# libmtnops
CONSTANTLY IN DEVELOPMENT
For years every time I needed an NG client or server I just wrote one into whatever code I had...  eventually I just copied old files into my code.  Now I decided to make an actual library out of the same files I've been copying around for a while...  This currently includes my NG client and server, my configuration routine, and will hopefully eventually include my general purpose INDI client.


## Build
 Simply use the Makefile with 

```
make
```
This will build the ```libmtnops.a``` library, as well as server_example and client_example

To build into other projects, first look at server_example.c and client_example.c to see how its implemented.  I suggest you just copy libmtnops.a and libmtnops.h into your working direcotry and build with a command like:

```
gcc server_example.c -L. -lmtnops -o server_example
```

## running
libmtnops.a is a library.  Copy it into the working directory of whatever project you are working on along with the libmtnops.h

server_example is a standalone application.  Start it with:
```
./server_example
```
client_example is a standalone application that can talk to server_example.  Start it with:
```
./client_example
```


## Files
client_example.c: barebones example of how to use the NG client

libmtnops.conf: example of a config file for the configure routine

ngclient.c: client routines for the NG protocol

server_example.c:  barebones example of how to use the NG client

configure.c: routines for configure

libmtnops.h: the header file to be included in programs using this lib

ngserver.c: server routines for the NG protocol

