# Makefile for vgraph

TARGET = mpdtimeratio
LIBS = "-lmpdclient"
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
CFLAGS += -march=native -O2 -fstack-protector-strong

.PHONY: default all clean

default: clean $(TARGET)
all: default

#OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJECTS = $(patsubst %.c, %.o, $(TARGET).c)
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
