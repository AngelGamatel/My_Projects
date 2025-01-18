FLAGS = -fno-elide-constructors -std=c++11 
a: arr.o main.o  
	g++ $(FLAGS) arr.o main.o
main.o: main.cpp libs.h
	g++ $(FLAGS) main.cpp -c
arr.o: arr.cpp libs.h
	g++ $(FLAGS) arr.cpp -c
