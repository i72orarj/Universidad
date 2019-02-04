#
# Makefile for Mobnet
#

SHELL = bash

LIBS = -lpthread
# Solaris -lposix4

CFLAGS = -Wall -g
CC = gcc

SRCS = esta.c fcfs.c genera.c sim.c sjf.c

OBJS := $(SRCS:.c=.o)



all: sim
	

sim: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o sim
	
depend:
	makedepend -- $(CFLAGS) -- $(SRCS) 
clean:
	rm -f $(OBJS); rm -f sim
