all:
	gcc -Wall -g *.c -o test

run: all
	./test sample.txt out.txt

debug:
	gdb --args test sample.txt out.txt