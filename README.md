# cpptrace

Minimal code example to build ax external library for tracing functions

Instructions :

* build the trace library :

  $ gcc -Wall -Wextra -shared -fPIC -O2 trace.c -o libtrace.so

* build your own program with instrumentation :

  $ g++ -Wall -Wextra -I. -finstrument-functions -rdynamic myprogram.cxx -ltrace -ldl -o myprogram.x

Limitations :

* \*.nix et \*.nux (POSIX ?)
* GNU for addresses query
