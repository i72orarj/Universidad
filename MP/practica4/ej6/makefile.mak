crucigrama.x: libMemoria.a main.o ficheros.o crucigrama.o
	gcc -o crucigrama.x main.o ficheros.o crucigrama.o libMemoria.a

main.o: main.c
	gcc -c main.c

ficheros.o: ficheros.c
	gcc -c ficheros.c

crucigrama.o: crucigrama.c
	gcc -c crucigrama.c

libMemoria.a: reservaMemoria.o liberaMemoria.o
	ar -rsv libMemoria.a reservaMemoria.o liberaMemoria.o

reservaMemoria.o: reservaMemoria.c
	gcc -c reservaMemoria.c

liberaMemoria.o: liberaMemoria.c
	gcc -c liberaMemoria.c

clean:
	@rm *.o
