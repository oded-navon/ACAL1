CC=gcc
CFLAGS=-I.
DEPS = Main.h ArgParser.h Trace.h Utils.h

iss: Main.o
   $(CC) -o iss Main.o $(CFLAGS)

Main.o: main.c Utils.o Trace.o ArgParser.o $(DEPS)
   $(CC) -c main.c $(CFLAGS)

Utils.o: Utils.c Globals.o $(DEPS)
   $(CC) -c Utils.c $(CFLAGS)

Globals.o: Globals.c
   $(CC) -c Globals.c $(CFLAGS)

ArgParser.o: ArgParser.c
   $(CC) -c ArgParser.c $(CFLAGS)

Trace.o: v.c
   $(CC) -c Trace.c $(CFLAGS)