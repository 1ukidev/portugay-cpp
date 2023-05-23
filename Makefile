all:
	g++ -O2 -pipe portugay.cpp -o portugay

install:
	cp portugay /usr/local/bin/portugay

uninstall:
	rm /usr/local/bin/portugay

clean:
	rm portugay
