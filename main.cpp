#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "FunctionalDependency.hpp"
#include "FunctionalDependencySet.hpp"

#include "CalculateFDClosure.hpp"
#include "CalculateAttributeClosure.hpp"
#include "CalculateMinimalCover.hpp"
#include "CalculateAllCandidateKeys.hpp"
#include "ChaseTest.hpp"

int main() {
	/*Relation R("ABCDEF");

	Relation R1("ABC");
	Relation R2("AD");
	Relation R3("DE");
	Relation R4("CEF");

	std::vector<Relation> decomposition = {
		R1, R2, R3, R4
	};

	FDSet S({
		FD("A->B"),
		FD("BC->D"),
		FD("E->C"),
		FD("D->AE"),
		FD("C->F")
	});*/

	Relation R("ABCD");

	Relation R1("AD");
	Relation R2("BC");
	Relation R3("CD");

	std::vector<Relation> decomposition = {
		R1, R2, R3
	};

	FDSet S({
		FD("B->AD")
	});

	std::ofstream out("chaseout.tex");

	std::cout << ChaseTest(R, decomposition, S, &out) << std::endl;

	out.close();
}
