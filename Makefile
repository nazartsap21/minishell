minishell: main_minishell

main_minishell: main.o parser.o shell.o
	gcc main.o parser.o shell.o -o minishell.exe

main.o: main.c main.h shell.h
	gcc main.c -c -o main.o

parser.o: parser.c parser.h
	gcc parser.c -c -o parser.o

shell.o: shell.c shell.h parser.h
	gcc shell.c -c -o shell.o

clean:
	rm -f *.o *.exe