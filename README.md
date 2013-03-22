PolarSSL for Classic MacOS
==========================

**This is not extensively tested, and may not be secure at all!**
**Don't blame me for any data breaches!**

This is a port of the PolarSSL library to the classic MacOS. Since it uses MacTCP for sockets it may work as far back as System 6, but the earliest I've tested is 7.5.5. The compiler is CodeWarrior Pro 1, and being that it's from 1997 there are some things missing and some incompatibilities I had to work around. However, PolarSSL is very portable and so the changes were small for the most part.

Some of the incompatibilities are handled through a library of mine, [libcompat](/leitec/libcompat), which provides basic C99 integer types and a few functions missing in CodeWarrior Pro 1's MSL.

Mac-specific things:
- [x] MacTCP client sockets using our `net_mactcp` module
- [x] MacOS-specific file handling for X509 certs (untested; may have problems with ':' separators instead of '/')
- [x] HAVEGE using processor ticks for PowerPC (may need 603 or higher) or OS ticks for 68k. No analysis has been done to determine if this is random enough.
- [x] ASM-accelerated bignum on PowerPC (not yet committed)
- [ ] ASM-accelerated bignum on 68k
- [ ] MacTCP server sockets
- [ ] timing stuff (alarms, etc.) that I'm not sure are used for anything other than benchmarks

The later stages of development were done under Classic on MacOS X Tiger. This is to facilitate using git, which is not available for classic MacOS (not yet, at least). CWPro1 only sees files that have the resource type 'TEXT' so after checkout you have to do something like:

    find . -type f -name \*.[ch] -print0 | xargs -0 /Developer/Tools/SetFile -c CWIE -t TEXT

This sets the file type and creator type so that CodeWarrior can edit it. In CW each file can be set to Mac or UNIX-style line feeds, so to make things easier we use UNIX-style for everthing.

I think that's it for now. Let me know if you are the other person in the world that is interested in classic MacOS development.
