all:
	gcc -Wall -Wextra -Iinclude -c src/server.c -o build/server.o
	gcc -Wall -Wextra -Iinclude -c src/client.c -o build/client.o
	gcc build/server.o -o bin/server
	gcc build/client.o -o bin/client