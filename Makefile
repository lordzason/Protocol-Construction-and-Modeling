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
Main: Main.o Client.o Server.o 
	$(CC) -I/usr/include/nacl -lnacl -o Main Main.o Client.o Server.o

Main.o: Main.c crypto_box.h
	$(CC) $(CFLAGS) -c Main.c 

Client.o: Client.c crypto_box.h
	$(CC) $(CFLAGS) -c Client.c 

Server.o: Server.c crypto_box.h
	$(CC) $(CFLAGS) -c Server.c 

clean:
	rm -f *.o *~ core*

