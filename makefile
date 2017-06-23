
CC=c99
CFLAGS=-c -Wall

all: clean heap
	./heap

heap: heap.o helper.o
	$(CC) -o heap heap.o helper.o

helper.o:
	$(CC) $(CFLAGS) helper.c

heap.o:
	$(CC) $(CFLAGS) heap.c

clean:
	rm -rf *.o heap
