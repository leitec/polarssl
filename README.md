PolarSSL for Classic MacOS
==========================

**This is not extensively tested, and may not be secure at all!**
**Don't blame me for any data breaches!**

This is a port of the PolarSSL library to the classic MacOS. Since it uses MacTCP for sockets it may work as far back as System 6, but the earliest I've tested is 7.5.5. The compiler is CodeWarrior Pro 1, and being that it's from 1997 there are some things missing and some incompatibilities I had to work around. However, PolarSSL is very portable and so the changes were small for the most part.

Some of the incompatibilities are handled through a library of mine, [libcompat](https://github.com/leitec/libcompat), which provides basic C99 integer types and a few functions missing in CodeWarrior Pro 1's MSL.

Mac-specific things
-------------------
- [X] MacTCP client sockets using our `net_mactcp` module
- [X] MacOS-specific file handling for X.509 certs (untested; may have problems with ':' separators instead of '/')
- [X] HAVEGE using processor ticks for PowerPC (may need 603 or higher) or OS ticks for 68k. (see below)
- [X] ASM-accelerated bignum on PowerPC
- [ ] ASM-accelerated bignum on 68k
- [ ] MacTCP server sockets
- [ ] timing stuff (alarms, etc.) that I'm not sure are used for anything other than benchmarks

The later stages of development were done under Classic on MacOS X Tiger. This is to facilitate using git, which is not available for classic MacOS (not yet, at least). CWPro1 only sees files that have the resource type 'TEXT' so after checkout you have to do something like:

    find . -type f -name '*.[ch]' -print0 | xargs -0 /Developer/Tools/SetFile -c CWIE -t TEXT

This sets the file type and creator type so that CodeWarrior can edit it. In CW each file can be set to Mac or UNIX-style line feeds, so to make things easier we use UNIX-style for everthing.

**Randomness and Entropy**

This port uses PolarSSL's built-in entropy routines, which use the [HAVEGE](http://www.irisa.fr/caps/projects/hipsor/) RNG and some sort of tick counter (which HAVEGE also uses). On platforms that support it the platform's native PRNG is also used, but MacOS does not have such a facility.

I am not a crypto expert by any means, but I believe there is sufficient entropy to make this port reasonably secure. Tests using [ent](http://www.fourmilab.ch/random/) on 1MB of random data are within recommended values:

    Entropy = 7.999839 bits per byte.

    Optimum compression would reduce the size
    of this 1048576 byte file by 0 percent.

    Chi square distribution for 1048576 samples is 234.21, and randomly
    would exceed this value 82.05 percent of the times.

    Arithmetic mean value of data bytes is 127.4068 (127.5 = random).
    Monte Carlo value for Pi is 3.146587931 (error 0.16 percent).
    Serial correlation coefficient is 0.000725 (totally uncorrelated = 0.0).

and for 68K:

    Entropy = 7.999835 bits per byte.

    Optimum compression would reduce the size
    of this 1048576 byte file by 0 percent.

    Chi square distribution for 1048576 samples is 239.21, and randomly
    would exceed this value 75.32 percent of the times.

    Arithmetic mean value of data bytes is 127.5510 (127.5 = random).
    Monte Carlo value for Pi is 3.139195020 (error 0.08 percent).
    Serial correlation coefficient is 0.001349 (totally uncorrelated = 0.0).

(each run is different, but still in the same ballpark.)

All that said, **I make absolutely no guarantees about security**.
