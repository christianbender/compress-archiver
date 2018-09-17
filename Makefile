compress: main.o compress.o
	gcc -o compress main.o compress.o

main.o: main.c 
	gcc -c main.c 

compress.o: compress.c
	gcc -c compress.c

clean:
	rm main.o compress.o compress

