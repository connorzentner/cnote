CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncurses
TARGET = cnote

all: $(TARGET)

$(TARGET): cnote.c flags.c
	$(CC) $(CFLAGS) cnote.c flags.c -o $(TARGET) $(LIBS)

clean: 
	rm -f $(TARGET)
