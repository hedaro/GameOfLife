CC = gcc

INCLUDES = include/GameOfLife.h

CFLAGS = -Wall

LIBS = -lSDL2 -lGL

SRCS = src/main.c

TARGET = bin/GameOfLife

$(TARGET): $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm $(TARGET)
