CC=g++
CFLAGS=-Wall -std=c++11
COMPILE = $(CC) $(CFLAGS)
LIBS=-lboost_program_options

SOURCES=$(wildcard *.cc)

BIN=bfcc


all: $(BIN)


$(BIN): $(SOURCES)
	$(COMPILE) $(SOURCES) $(LIBS) -o $(BIN)

install-bin: $(BIN)
	cp $(BIN) /usr/local/bin/

clean:
	rm $(BIN)

install: install-bin clean

uninstall:
	rm /usr/local/bin/$(BIN)
