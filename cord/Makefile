all:
	gcc server.c -lpthread -lsqlite3 -o server
	gcc client.c -o client
clean:
	rm server client server.c~ client.c~ head.h~ *.db -rf

