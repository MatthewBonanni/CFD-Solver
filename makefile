out: main.o dsys.o
	g++ main.o dsys.o -o out

main.o: main.cpp
	g++ -std=c++17 -c main.cpp
dsys.o: dsys.cpp
	g++ -std=c++17 -c dsys.cpp

clean:
	rm *.o out