hw4: encrypt3.o hw4.c
	gcc -o hw4 -g hw4.c

tablecheck.o: tablecheck.c
	gcc -g -c -Wall encrypt.c

encrypt.o: encrypt.c tablecheck.o
	gcc -g -c -Wall encrypt.c

encrypt3.o: encrypt3.c encrypt.o
	gcc -g -c -Wall encrypt3.c





clean:
	rm -f *.o hw4
