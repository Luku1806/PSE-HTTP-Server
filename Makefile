# Makefile to build the HTTP-Server

SHELL = /bin/sh  # The shell in which to execute make rules.

CC=gcc
CFLAGS =
LDFLAGS = -lssl -lcrypto -lmagic
TARGET = http_server


src = $(wildcard src/*.c)
obj = $(src:.c=.o)


all: $(TARGET)


$(TARGET): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)