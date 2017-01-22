#******************************************************************************
## Function name: Makefile
##
## DESCRIPTION:   A set of commands to compile all files in project2
##
## Parameters:    n/a
##
## Return values: n/a
##
##*****************************************************************************

# Declare the variables
CC = g++

CFLAGS = -c

# This target will compile all the files
all: hello

# This target will compile all the files
hello: main.o getaddress.o llist.o
	$(CC) -o project2 main.o getaddress.o llist.o

# This target will compile main.o only
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

# This target will compile address.o only
getaddress.o: getaddress.cpp
	$(CC) $(CFLAGS) getaddress.cpp

# This target will compile llist.o only
llist.o: llist.cpp
	$(CC) $(CFLAGS) llist.cpp

# This will activate DEBUGMODE
debug:
	$(CC) -DDEBUGMODE $(CFLAGS) main.cpp getaddress.cpp llist.cpp
	$(CC) -o project2 main.o getaddress.o llist.o

# This target will remove the executable and all object files
clean:
	rm -rf *o project2
