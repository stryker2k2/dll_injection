shared_lib.dll: shared_lib.o
	gcc -shared shared_lib.o -o shared_lib.dll

shared_lib.o: shared_lib.c
	gcc -c -D BUILD_MY_DLL shared_lib.c

clean:
	rm *.dll