CC=gcc

hellomake: bct.o crypto.o main.o
	$(CC) -o a.out bct.o crypto.o main.o
