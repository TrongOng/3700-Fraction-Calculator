output: main.o dictionary.o fraction.o
	g++ -o output main.o dictionary.o fraction.o

main.o: main.cpp dictionary.h stack.h stack.h
	g++ -c main.cpp

dictionary.o: dictionary.cpp dictionary.h fraction.h
	g++ -c dictionary.cpp

fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc

clean:
	rm*.o output