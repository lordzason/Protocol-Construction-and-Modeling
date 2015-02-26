#Authors : Zhi Chen & Albert Owusu-Asare
#Created : Thu Feb 26 01:13:44 CST 2015

#We will be using the gcc compiler
# Use the gcc compiler
CC = cc

# Set compilation flags
#   -ansi (check syntax against the American National Standard for C
CFLAGS = -Wall -g

#----------------------------------------------------------------------------
# build rules:
#
# Each rule takes the following form>  (Note there MUST be a tab,
# as opposed to several spaces, preceeding each command.
#
# target_name:  dependency_list
#	command(s)


all: Main


# List program components, what they depend on, and how to compile each
Main:  Client.o Server.o devurandom.o
	$(CC) -I/usr/include/nacl  -o Main  Client.o Server.o devurandom.o Main.c -lnacl

Client.o: Client.c 
	$(CC) $(CFLAGS) -c -I/usr/include/nacl Client.c 

Server.o: Server.c 
	$(CC) $(CFLAGS) -c -I/usr/include/nacl Server.c 

devurandom.o: devurandom.c 
	$(CC) $(CFLAGS) -c -I/usr/include/nacl devurandom.c 

clean:
	rm -f *.o *~ core*

