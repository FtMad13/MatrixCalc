# author: jirasant
# date: 22.5.2022

PROGRAM=jirasant
CC=g++
CFLAGS= -std=c++11 -Wall -Wpedantic -Wextra -g

SRCDIR = src
SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
HDR = $(shell find $(SRCDIR)/ -type f -name '*.h')

all: compile doc run clean

compile: $(PROGRAM)

doc: $(SRC) $(HDR)
	doxygen
	cp -r ./doc/html/* ./doc

run:
	./$(PROGRAM)
clean:
	rm -rf doc
	rm -f $(PROGRAM)




$(PROGRAM): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

