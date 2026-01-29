CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncurses
TARGET = cnote

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LIBS)

clean: 
	rm -f $(TARGET)
