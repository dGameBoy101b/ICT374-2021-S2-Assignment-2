#makefile for prntCWD testing

testPrntCWD: testPrntCWD.o prntCWD.o
	gcc testPrntCWD.o prntCWD.o -o testPrntCWD -Wall

testPrntCWD.o: testPrntCWD.c prntCWD.h
	gcc -c testPrntCWD.c -Wall

prntCWD.o: prntCWD.c prntCWD.h
	gcc -c prntCWD.c -Wall

clean:
	rm *.o
