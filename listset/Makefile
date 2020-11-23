# Makefile
CC = clang
CFLAGS=-I.

build: listset.c
	echo "Building"
	cc -g listset-main.c listset.c listset.h -I. -o listset

test: 
	echo "Debug"
	cc -g listset-main.c listset.c listset.h -I. -o listset
	./listset + knife + spoon + fork + no - knife + is + there - fork =

clean:
	rm -rf listset

submission_archive:
	tar -cvf listset_submission.tar *.h *.c