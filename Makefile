CC=clang

bin/shim.so: src/shim.c
	$(CC) -Wall -Wl,--no-as-needed -O2 -fpic -shared -ldl -o $@ $<
