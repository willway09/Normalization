all: FunctionalDependency.o AttributeSet.o FunctionalDependencySet.o
	g++ -std=c++17 -o main main.cpp FunctionalDependency.o AttributeSet.o FunctionalDependencySet.o

FunctionalDependency.o: FunctionalDependency.cpp FunctionalDependency.hpp
	g++ -std=c++17 -c -o FunctionalDependency.o FunctionalDependency.cpp

AttributeSet.o: AttributeSet.cpp AttributeSet.hpp
	g++ -std=c++17 -c -o AttributeSet.o AttributeSet.cpp

FunctionalDependencySet.o: FunctionalDependencySet.cpp FunctionalDependencySet.hpp
	g++ -std=c++17 -c -o FunctionalDependencySet.o FunctionalDependencySet.cpp

clean:
	@-rm main AttributeSet.o FunctionalDependency.o
