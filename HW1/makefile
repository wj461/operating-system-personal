CC=gcc

build: cp.o time_mmap.o time_pipe.o
	$(CC) -o cp.exe cp.c
	$(CC) -o time_mmap.exe time_mmap.c
	$(CC) -o time_pipe.exe time_pipe.c

clean:
	rm -f *.exe
	rm -f *.o