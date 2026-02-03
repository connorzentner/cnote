CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncurses
TARGET = cnote

all: $(TARGET)

$(TARGET): cnote.c
	$(CC) $(CFLAGS) cnote.c -o $(TARGET) $(LIBS)

clean: 
	rm -f $(TARGET)
