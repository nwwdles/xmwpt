VERCMD  ?= git describe --tags 2> /dev/null
VERSION := $(shell $(VERCMD) || cat VERSION)

CPPFLAGS += -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\"
CFLAGS   += -std=c99 -pedantic -Wall -Wextra -DJSMN_STRICT
LDFLAGS  ?=
LDLIBS    = $(LDFLAGS) -lXfixes -lX11

PREFIX    ?= /usr/local
BINPREFIX ?= $(PREFIX)/bin

SRC = xmwpt.c
OBJ := $(SRC:.c=.o)

.PHONY: all
all: xmwpt

.PHONY: clean
clean:
	rm -f $(OBJ) xmwpt

.PHONY: install
install:
	mkdir -p "$(DESTDIR)$(BINPREFIX)"
	cp -pf xmwpt "$(DESTDIR)$(BINPREFIX)"

$(OBJ): Makefile

xmwpt: $(OBJ)
