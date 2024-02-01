all: r.c r.h makefile
	clang -ffast-math -Os r.c -oc -lm
	./c	
clean:
	rm -f c
