TARGET=zombie
CFLAGS=-g -Wall
OBJS=zombie.o
CC=gcc

$(TARGET):zombie.c
	$(CC) -c zombie.c
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)
