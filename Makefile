#########################################
# makefile for libmtnops				  	#
################objects##################
LIBMTNOPS_OBJS = ngserver.o ngclient.o configure.o

###############binaries##################

all: clean libmtnops.a server_example client_example

ngserver.o: ngserver.c libmtnops.h
		gcc -c ngserver.c
		
ngclient.o: ngclient.c libmtnops.h
		gcc -c ngclient.c
		
configure.o: configure.c libmtnops.h
		gcc -c configure.c
		
libmtnops.a: $(LIBMTNOPS_OBJS)
		ar rcs $@ $^
		
server_example: server_example.c libmtnops.a
		gcc server_example.c -L. -lmtnops -o server_example

client_example: client_example.c libmtnops.a
		gcc client_example.c -L. -lmtnops -o client_example

###############Utilities################	
		
clean:
		rm -rf *.o *.a server_example client_example
