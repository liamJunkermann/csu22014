# Makefile
CC = clang
CFLAGS=-I.

clean:
	rm -rf listset

build: listset.c
	echo "Building"
	$(CC) -o listset listset-main.c listset.c listset.h
	
test: 
	echo "Debug"
	cc -g listset-main.c listset.c listset.h -I. -o listset
	./listset + knife + spoon + fork + no - knife + is + there - fork =

submission_archive:
	tar -cvf listset_submission.tar *.h *.c