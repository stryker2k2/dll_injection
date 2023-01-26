client.exe: client.o
	gcc client.o mmLoader.o -o client.exe

client.o: mmLoader.o
	gcc -c client.c

mmLoader.o:
	gcc -c mmLoader.c

clean:
	del *.exe

run:
	./client.exe

.PHONY: client.exe client.o clean run