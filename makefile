program: main.o member.o resource.o library.o
	g++ -std=c++11 -o program main.o member.o resource.o library.o
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
library.o: library.cpp
	g++ -std=c++11 -c library.cpp
member.o: member.cpp
	g++ -std=c++11 -c member.cpp
resource.o: resource.cpp
	g++ -std=c++11 -c resource.cpp
