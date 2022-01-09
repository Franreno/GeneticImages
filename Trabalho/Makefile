main:
	g++ -c main.cpp -o main.o -Wall -Werror

ag:
	g++ -c ag.cpp -o ag.o -Wall -Werror

trab: main ag
	g++ main.o ag.o -o trab

all: trab

run: all
	./trab