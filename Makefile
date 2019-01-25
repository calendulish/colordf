CC = gcc
CFLAGS = -Wall -O2 -lm
INSTALL = /usr/bin/install
SRCS = $(wildcard src/*.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TARGET = cutedf
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

cutedf: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -f $(OBJS) $(TARGET)

install: all
	$(INSTALL) -D -s $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

.PHONY: all install clean
