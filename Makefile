a: problem6.o
	g++ -std=c++11 -g -Wall problem6.o -o a

problem6.o: problem6.cpp
	g++ -std=c++11 -g -Wall -c problem6.cpp

clean:
	rm *.o a
