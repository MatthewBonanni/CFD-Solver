dsys: dsys_ab.o
	g++ dsys_ab.o -o dsys

dsys_ab.o: dsys_ab.cpp
	g++ -std=c++11 -c dsys_ab.cpp

clean:
	rm *.o dsys