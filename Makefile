commpile_all :
	cc -c *.c
	cc dccalculator.c -o dccalculator

smallsh: 
	make commpile_all
	cc -o smallsh dcmain_smallsh.o dcuserin.o dcruncommand.o dcproc_line.o dcproject.o

remove:
	rm *.o
	rm smallsh
	rm dccalculator