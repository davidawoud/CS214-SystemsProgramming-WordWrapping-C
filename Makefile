CCFLAGS = -ggdb -Wall

compile: ww.c
	gcc $(CCFLAGS) ww.c -o ww

submit: ww.c
	tar -cvzf proj2.tar ww.c Makefile README.txt

clean:
	rm ww