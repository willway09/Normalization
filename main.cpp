#include <iostream>
#include <sstream>
#include <algorithm>

#include "FunctionalDependency.hpp"
#include "FunctionalDependencySet.hpp"

#include "CalculateFDClosure.hpp"
#include "CalculateAttributeClosure.hpp"
#include "CalculateMinimalCover.hpp"

int main() {
	/*Relation R("ABC");

	FDSet answer = FDSet({
			FD("A->BC"),	FD("B->C"),	FD("ABC->A"),	FD("C->C"),	FD("AC->AC"),	FD("B->B"),	FD("ABC->BC"),
			FD("BC->BC"),	FD("BC->B"),	FD("AB->BC"),	FD("A->ABC"),	FD("ABC->C"),	FD("AC->C"),	FD("AC->AB"),
			FD("A->A"),	FD("AC->B"),	FD("A->AB"),	FD("AB->AC"),	FD("AB->B"),	FD("ABC->AB"),	FD("BC->C"),
			FD("ABC->AC"),	FD("AB->AB"),	FD("AB->C"),	FD("AC->BC"),	FD("AB->ABC"),	FD("A->C"),	FD("A->AC"),
			FD("AC->ABC"),	FD("ABC->ABC"),	FD("ABC->B"),	FD("AB->A"),	FD("A->B"),	FD("B->BC"),	FD("AC->A")
	});

	FDSet prompt({FD("A->B"), FD("B->C")});
	FDSet result = CalculateFDClosure(prompt, R);

	std::cout << "Prompt: " << std::endl << prompt << std::endl << std::endl;
	std::cout << "Result: " << std::endl << result << std::endl << std::endl;
	std::cout << "Answer: " << std::endl << answer << std::endl << std::endl;

	std::cout << "Correct: " << (result == answer ? "Yes" : "No") << std::endl << std::endl;;

	std::cout << "Difference1: " << std::endl << (answer - result) << std::endl << std::endl;
	std::cout << "Difference2: " << std::endl << (result - answer) << std::endl << std::endl;

	AttributeSet A("ABC");
	AttributeSet B("D");*/

	/*Relation R("ABCGHI");
	FDSet fds = FDSet({
		FD("A->B"), FD("A->C"), FD("CG->H"), FD("CI->G")
	});

	AttributeSet attributes = AttributeSet("AG");

	auto closure = CalculateAttributeClosure(fds, attributes);

	std::cout << "Closure of " << attributes << ": " << closure << std::endl;*/


	//Relation R("ABD");
	//FDSet F({FD("B->A"), FD("D->A"), FD("AB->D")});

	//FDSet F({FD("A->BC"), FD("B->C"), FD("A->B"), FD("AB->C")});


	Relation R("ABCD");

	FDSet F({FD("A->BC"), FD("C->AB"), FD("B->AC")});


	std::cout << CalculateMinimalCover(F) << std::endl;
	std::cout << CalculateNonstandardMinimalCover(F) << std::endl;

 	auto ans1 = FDSet({FD("A->B"), FD("C->A"), FD("B->C")});

	std::cout << 
		(
			CalculateFDClosure(F, R)
				==	
			CalculateFDClosure(ans1, R)
		)
	<< std::endl;
}
