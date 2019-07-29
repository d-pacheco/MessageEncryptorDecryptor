encrytion: main.o encrypt.o
	gcc -Wall -std=c99 -o encryption main.o encrypt.o

main.o: main.c encrypt.h
	gcc -Wall -std=c99 -c main.c

encrypt.o: encrypt.c encrypt.h
	gcc -Wall -std=c99 -c encrypt.c

clean:
	rm -f encryption *.o
