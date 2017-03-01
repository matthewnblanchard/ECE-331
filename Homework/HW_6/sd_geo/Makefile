TARGET=sd_geo
CFLAGS=-g -Wall
OBJS=sd_geo.o
CC=gcc

$(TARGET):sd_geo.c
	$(CC) -c sd_geo.c
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)
