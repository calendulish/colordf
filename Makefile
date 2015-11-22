CC = gcc
CFLAGS = -Wall -O2 -lm
INSTALL = /usr/bin/install
OBJS = cutedf.o common.o hash.o colors.o conf.o stat.o
TARGET = cutedf
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

cutedf: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm -f *.o $(TARGET)

install: all
	$(INSTALL) -D -s $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

.PHONY: all install clean
