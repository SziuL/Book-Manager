all: teste

teste: funcionalidades.o main.o
	gcc -o teste funcionalidades.o main.o

estruturas.o: estruturas.h
	gcc -c estruturas.h -Wall -Werror -Wextra

funcionalidades1.o: funcionalidades.c estruturas.h
	gcc -c funcionalidades.c -Wall -Werror -Wextra

funcionalidades.o: funcionalidades.c funcionalidades.h
	gcc -c funcionalidades.c -Wall -Werror -Wextra

main.o: main.c funcionalidades.h
	gcc -c main.c -Wall -Werror -Wextra

clean:
	rm -rf *.o teste