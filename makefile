all: teste
teste: main.o geometria.o
	gcc main.o geometria.o -o teste
main.o: main.c
	gcc -c main.c
geometria.o: geometria.c
	gcc -c geometria.c

clean:
	rm *.o teste
