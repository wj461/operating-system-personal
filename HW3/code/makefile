CC := gcc

build: fibonacci.o mutex_biridge.o virtual_address.o
	$(CC) -o ./build/fibonacci.exe fibonacci.c
	$(CC) -o ./build/mutex_biridge.exe mutex_biridge.c
	$(CC) -o ./build/virtual_address.exe virtual_address.c

clean:
	rm -f ./build/*.exe
	rm -f *.o