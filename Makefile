CC = /usr/bin/gcc

compress: main.o compress.o
	$(CC) -o compress main.o compress.o

main.o: main.c 
	$(CC) -c main.c 

compress.o: compress.c
	$(CC) -c compress.c

clean:
	rm main.o compress.o compress

