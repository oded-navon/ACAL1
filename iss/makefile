CC=gcc
CFLAGS=-I. -std=c99
DEPS = Main.h ArgParser.h Trace.h Utils.h

iss: Main.c Utils.c Trace.c ArgParser.c Globals.c $(DEPS)
	$(CC) -o iss Main.c Utils.c Trace.c ArgParser.c Globals.c -Wall $(CFLAGS)

clean:
	rm -f Globals.o ArgParser.o Trace.o Utils.o Main.o iss