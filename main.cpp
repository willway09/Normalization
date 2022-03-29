#include <iostream>
#include <sstream>

#include "FunctionalDependency.hpp"
#include "FunctionalDependencySet.hpp"

int main() {
	FDSet fds( 
		{
			FD("A->BC"),	FD("B->C"),	FD("ABC->A"),	FD("C->C"),	FD("AC->AC"),	FD("B->B"),	FD("ABC->BC"),
			FD("BC->BC"),	FD("BC->B"),	FD("AB->BC"),	FD("A->ABC"),	FD("ABC->C"),	FD("AC->C"),	FD("AC->AB"),
			FD("A->A"),	FD("AC->B"),	FD("A->AB"),	FD("AB->AC"),	FD("AB->B"),	FD("ABC->AB"),	FD("BC->C"),
			FD("ABC->AC"),	FD("AB->AB"),	FD("AB->C"),	FD("AC->BC"),	FD("AB->ABC"),	FD("A->C"),	FD("A->AC"),
			FD("AC->ABC"),	FD("ABC->ABC"),	FD("ABC->B"),	FD("AB->A"),	FD("A->B"),	FD("B->BC"),	FD("AC->A")
		}
	);
	std::cout << fds << std::endl;
}
