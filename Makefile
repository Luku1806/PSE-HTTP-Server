# Makefile to build the HTTP-Server

SHELL = /bin/sh  # The shell in which to execute make rules.

CC=gcc
CFLAGS =
LDFLAGS = -lssl -lcrypto -lmagic
TARGET = http_server
DESTDIR = /usr/local


src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)


all: $(TARGET)
	@echo "Successfully compiled HTTP-Server! Run it by typing './$(TARGET)'"


$(TARGET): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) $(TARGET)
	@echo "Successfully cleaned HTTP-Server! All objects and binaries were removed!"


.PHONY: install
install: $(TARGET)
	# Copy program
	mkdir -p $(DESTDIR)/bin
	cp $< $(DESTDIR)/bin/$(TARGET)

	# Copy webroot
	cp -r webroot $(DESTDIR)/

	@echo "Successfully installed HTTP-Server!


.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)/bin/$(TARGET)
	rm -f -r $(DESTDIR)/webroot
	@echo "Successfully uninstalled HTTP-Server! Binary and webroot were deleted!"