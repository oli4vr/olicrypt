all:
	gcc -c sha512.c -o sha512.o -O3
	gcc -c encrypt.c -o encrypt.o -O3
	gcc olicrypt.c -o olicrypt -O3 sha512.o encrypt.o
install:
	mkdir -p ~/bin 2>/dev/null
	cp olicrypt ~/bin
uninstall:
	rm -rf ~/bin/olicrypt
clean:
	rm -f olicrypt *.o
