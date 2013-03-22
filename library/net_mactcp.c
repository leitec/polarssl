/*
 * This is based on code I wrote for my library 'imcomm' around 2005,
 * which was itself based on some unfinished code in PuTTY source.
 * I'm not sure where this places this code license-wise.
 *
 * To use:
 * - need two structures, mactcp_inst and mactcp_conn
 * - need to run mactcp_init() on your mactcp_inst to load MacTCP
 *   this is needed only once per program, no matter how many sockets
 *   or connections are done. This may be a global, since you'll need it
 *   anytime you do a mactcp_connect() (but not send/recv since a pointer
 *   is kept after mactcp_connect())
 * - mactcp_connect() and everything else uses mactcp_conn to keep
 *   track of specific connections
 * - important: must close all connections; leaving open connections
 *   and quitting the program may result in crashes. (use mactcp_close())
 * - mactcp_send() and mactcp_recv() work like in BSD sockets.
 *
 * To use with PolarSSL:
 * - use ssl_set_bio(<ssl context>, mactcp_recv, &mc,
 *                                  mactcp_send, &mc);
 *   where mc is your mactcp_conn struct.
 * - use mactcp_connect(), mactcp_close(), etc. instead of
 *   net_connect(), net_close()
 *
 * -- leitec, 2013
 */

#include "polarssl/net_mactcp.h"
#include "polarssl/net.h"

ProcessSerialNumber psn;

static pascal void
mactcp_lookupdone(struct hostInfo * hi, char *cookie)
{
	volatile int   *donep = (int *) cookie;

	*donep = TRUE;
}

static pascal void
mactcp_asr(StreamPtr str, unsigned short event, Ptr cookie,
	   unsigned short termin_reason, struct ICMPReport * icmp)
{
	WakeUpProcess(&psn);
}

void
mactcp_close(mactcp_conn *c)
{
	TCPiopb         pb;
	OSErr	err;

	pb.ioCRefNum = c->i->refnum;
	pb.csCode = TCPClose;
	pb.tcpStream = c->s;
	pb.csParam.close.validityFlags = 0;
	pb.csParam.close.userDataPtr = (Ptr) c;
	PBControlSync((ParmBlkPtr) & pb);

	pb.ioCRefNum = c->i->refnum;
	pb.csCode = TCPAbort;
	pb.tcpStream = c->s;
	pb.csParam.abort.userDataPtr = (Ptr) c;
	PBControlSync((ParmBlkPtr) & pb);

	pb.ioCRefNum = c->i->refnum;
	pb.csCode = TCPRelease;
	pb.tcpStream = c->s;
	pb.csParam.create.userDataPtr = (Ptr) c;
	err = PBControlSync((ParmBlkPtr) & pb);
	
	if (err == noErr)
		free(pb.csParam.create.rcvBuff);
}

int mactcp_send(void *vc, const unsigned char *buf, size_t len)
{
	OSErr err;
	TCPiopb pb;
	wdsEntry wds[2];
	mactcp_conn *c = vc;
	
	wds[0].length = len;
	wds[0].ptr = (char *)buf;
	wds[1].length = 0;
	
	pb.ioCRefNum = c->i->refnum;
	pb.csCode = TCPSend;
	pb.tcpStream = c->s;
	pb.csParam.send.validityFlags = 0;
	pb.csParam.send.pushFlag = TRUE;
	pb.csParam.send.urgentFlag = 0;
	pb.csParam.send.wdsPtr = (Ptr)wds;
	
	err = PBControlSync((ParmBlkPtr) &pb);
	
	if(err == noErr) {
		return len;
	} else {
		printf("mactcp_send(): %d\n", err);
		return(POLARSSL_ERR_NET_SEND_FAILED);
	}
	
	return err;
}

int mactcp_recv(void *vc, unsigned char *inbuf, size_t len)
{
	TCPiopb pb;
	OSErr err;
	mactcp_conn *c = vc;
	
	pb.ioCRefNum = c->i->refnum;
	pb.csCode = TCPRcv;
	pb.tcpStream = c->s;
	pb.csParam.receive.commandTimeoutValue = 2;
	pb.csParam.receive.rcvBuff = (char *)inbuf;
	pb.csParam.receive.rcvBuffLen = len;
	
	err = PBControlSync((ParmBlkPtr) &pb);
	
	if(err == noErr) {
		return pb.csParam.receive.rcvBuffLen;
	} else {
		if(err == connectionClosing)
			return 0;
		
		printf("mactcp_recv(): %d\n", err);
		return(POLARSSL_ERR_NET_RECV_FAILED);
	}
}

OSErr mactcp_connect(mactcp_inst *i, mactcp_conn *c, char *hostname, short port)
{
	volatile int resolverDone = FALSE;
	struct hostInfo hi;
	size_t buflen;
	UDPiopb upb;
	TCPiopb pb;
	OSErr err;
	
	if(!i->initialized) {
		printf("mactcp_connect(): not initialized\n");
		return -1;
	}
	
	c->i = i;
	err = StrToAddr(hostname, &hi, i->mactcp_lookupdone_upp, (char *)&resolverDone);
	if(err == cacheFault) {
		while(!resolverDone)
			continue;
	}

	if(err != noErr && err != cacheFault)
		return err;
		
	/* get the max MTU size for this path */
	/* we use this to calculate the buffer size */
	upb.ioCRefNum = i->refnum;
	upb.csCode = UDPMaxMTUSize;
	upb.csParam.mtu.remoteHost = hi.addr[0];
	err = PBControlSync((ParmBlkPtr) &upb);
	
	if(err != noErr) {
		printf("mactcp_connect(): error getting MTU, err=%d\n", err);
		return err;
	}
	
	buflen = upb.csParam.mtu.mtuSize * 4 + 1024;
	if(buflen < 4096)
		buflen = 4096;
		
	pb.ioCRefNum = i->refnum;
	pb.csCode = TCPCreate;
	pb.csParam.create.rcvBuff = malloc(buflen);
	pb.csParam.create.rcvBuffLen = buflen;
	pb.csParam.create.notifyProc = i->mactcp_asr_upp;
	pb.csParam.create.userDataPtr = (Ptr)c;
	
	err = PBControlSync((ParmBlkPtr) &pb);
	if(err != noErr) {
		printf("mactcp_connect(): error creating TCP stream, err=%d", err);
		return err;
	}
	
	c->s = pb.tcpStream;
	
	pb.ioCRefNum = i->refnum;
	pb.csCode = TCPActiveOpen;
	pb.tcpStream = c->s;
	pb.csParam.open.validityFlags = 0;
	pb.csParam.open.remoteHost = hi.addr[0];
	pb.csParam.open.remotePort = port;
	pb.csParam.open.localPort = 0;
	pb.csParam.open.timeToLive = 0;
	pb.csParam.open.security = 0;
	pb.csParam.open.optionCnt = 0;
	pb.csParam.open.userDataPtr = (Ptr)c;
	err = PBControlSync((ParmBlkPtr) &pb);
	if(err != noErr) {
		printf("Error connecting TCP stream: %d\n", err);
		return err;
	}
	
	c->readable = 1;
	
	return noErr;
}

OSErr mactcp_init(mactcp_inst *i)
{
	OSErr err;
	
	err = OpenDriver("\p.IPP", &(i->refnum));
	if(err != noErr) {
		printf("Error initializing driver\n");
		return err;
	}
		
	err = OpenResolver(NULL);
	if(err != noErr) {
		printf("Error initializing resolver\n");
		return err;
	}
	
	i->mactcp_lookupdone_upp = NewResultProc(&mactcp_lookupdone);
	i->mactcp_asr_upp = NewTCPNotifyProc(&mactcp_asr);
	i->initialized = 1;
	
	GetCurrentProcess(&psn);

	return noErr;
}
