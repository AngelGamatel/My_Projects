FLAGS = -fopenmp -fno-elide-constructors -std=c++17

a: main.o arr.o Vector0.o Vector1.o
	g++ $(FLAGS) main.o arr.o Vector0.o Vector1.o
main.o : main.cpp libs.h
	g++ $(FLAGS) -c main.cpp
arr.o : arr.cpp libs.h
	g++ $(FLAGS) -c arr.cpp
Vector0.o : Vector0.cpp Vector0.h
	g++ $(FLAGS) -c Vector0.cpp	
Vector1.o : Vector1.cpp Vector1.h
	g++ $(FLAGS) -c Vector1.cpp	
