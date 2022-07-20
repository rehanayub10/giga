giga: giga.c
	$(CC) giga.c -o giga -Wall -Wextra -pedantic -std=c99

clean: 
	rm -rf giga
