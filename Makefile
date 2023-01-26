all: clean dll client move run

dll:
	(cd ./dll && make)

client:
	(cd ./client && make)

move:
	cp .\dll\shared_lib.dll .
	cp .\client\client.exe .

run:
	.\client.exe

clean:
	rm .\dll\shared_lib.dll || true
	rm .\client\client.exe || true
	rm shared_lib.dll || true
	rm client.exe || true

.PHONY: all dll client clean