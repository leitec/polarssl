#ifndef NET_MACTCP_H
#define NET_MACTCP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <Types.h>
#include <MacTCP.h>
#include <AddressXlation.h>

#include "polarssl/config.h"

typedef struct MacTCP_Instance {
	short refnum;
	short initialized;
	ResultUPP mactcp_lookupdone_upp;
	TCPNotifyUPP mactcp_asr_upp;
} mactcp_inst;

typedef struct MacTCP_Conn {
	mactcp_inst *i;
	StreamPtr s;
	int readable;
} mactcp_conn;

static pascal void mactcp_lookupdone(struct hostInfo * hi, char *cookie);
static pascal void mactcp_asr(StreamPtr str, unsigned short event, Ptr cookie,unsigned short termin_reason, struct ICMPReport * icmp);
void mactcp_close(mactcp_conn *c);
int mactcp_send(void *vc, const unsigned char *buf, size_t len);
int mactcp_recv(void *vc, unsigned char *inbuf, size_t len);

/*OSErr mactcp_send(mactcp_conn *c, char *buf, size_t len);
OSErr mactcp_recv(mactcp_conn *c, char *inbuf, size_t len);*/
OSErr mactcp_connect(mactcp_inst *i, mactcp_conn *c, char *hostname, short port);
OSErr mactcp_init(mactcp_inst *i);
#endif