giga: giga.c
	$(CC) giga.c -o giga -Wall -Wextra -pedantic -std=c99

giga2: giga2.c
	$(CC) giga2.c -o giga2 -Wall -Wextra -pedantic -std=c99

clean: 
	rm -rf giga
