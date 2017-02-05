all:
	g++ -o rsa1 -Wall -Werror -pedantic rsa1.cpp encryption.cpp decryption.cpp generate_keys.cpp utils.cpp -g -lcrypto
test:
	g++ -c -o ecryption.o encryption.cpp
	g++ -c -o decryption.o decryption.cpp
	g++ -c -o generate_keys.o generate_keys.cpp
	g++ -c -o utils.o utils.cpp
	g++ -c -o test.o test.cpp
	g++ -c -o mutest.o mutest.c
	mkmutest mutest.h ecryption.o decryption.o generate_keys.o utils.o test.o | cc -xc -c -o runmutest.o -
	g++ -o testprg mutest.o ecryption.o decryption.o generate_keys.o utils.o test.o runmutest.o -lcrypto
	./testprg -v
