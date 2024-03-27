CC := gcc

build: cp.o time_shm.o time_pipe.o
	$(CC) -o ./build/cp.exe cp.c
	$(CC) -o ./build/time_shm.exe time_shm.c
	$(CC) -o ./build/time_pipe.exe time_pipe.c

clean:
	rm -f ./build/*.exe
	rm -f *.o
	rm target.*