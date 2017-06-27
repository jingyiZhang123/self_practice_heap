
CC=c99
CFLAGS=-c -Wall

all: clean main
	./main

main: heap.o helper.o indexheap.o maxheap.o main.o
	$(CC) -o main heap.o helper.o main.o indexheap.o maxheap.o

main.o:
	$(CC) $(CFLAGS) main.c

helper.o:
	$(CC) $(CFLAGS) helper.c

heap.o:
	$(CC) $(CFLAGS) heap.c

maxheap.o:
	$(CC) $(CFLAGS) maxheap.c

indexheap.o:
	$(CC) $(CFLAGS) indexheap.c

clean:
	rm -rf *.o main
