out: main.o Dsys.o
	g++ main.o Dsys.o -o out

main.o: main.cpp
	g++ -std=c++17 -c main.cpp
Dsys.o: Dsys.cpp
	g++ -std=c++17 -c Dsys.cpp

clean:
	rm *.o out