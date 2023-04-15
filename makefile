CC = gcc
CFLAGS = -Wall -I./inc
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./build
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/sawlMD5

.PHONY: all clean

all: $(TARGET)
	cp ./build/sawlMD5 ./sawlMD5

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)
	clear

new:
	make clean
	make all

newStart:
	make new
	./sawlMD5