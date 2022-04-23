#pragma once
#include "FunctionalDependencySet.hpp"

FunctionalDependencySet CalculateMinimalCoverIntermediate(FunctionalDependencySet fds) {
	// Step 1: Initialize Fc
	auto Fc = fds;

	auto EmptySet = AttributeSet();

	// Step 2: Perform a left reduction of the FDs in Fc, i.e., identify and remove
	// all attributes on the left-hand sides of FDs in Fc that are extraneous
	auto temp = Fc;

	//std::cout << "Step 2" << std::endl;

	do {
		Fc = temp;
		for(auto fd : Fc) { 
			std::cout << "For $" << fd.from << " \\ar " << fd.to << "$:" << std::endl;
			std::cout << "\\begin{itemize}" << std::endl;

			for(auto a : fd.from) {
				auto missingAttrib = fd.from - AttributeSet({a});
				auto closure = CalculateAttributeClosure(Fc,  missingAttrib);
				if((missingAttrib != EmptySet) && (std::includes(closure.begin(), closure.end(), fd.to.begin(), fd.to.end()))) {
					temp = (temp - fd) + FD(fd.from - AttributeSet({a}), fd.to);
					//std::cout << "\\mincovertwo\t{" << fd.from << "}\t{" << fd.to << "}\t{" << a << "}\t{" << missingAttrib << "}\t{" << closure << "}\t{1}" << std::endl;
				} else {
					//std::cout << "\\mincovertwo\t{" << fd.from << "}\t{" << fd.to << "}\t{" << a << "}\t{" << missingAttrib << "}\t{" << closure << "}\t{0}" << std::endl;
				}
			}
			std::cout << "\\end{itemize}" << std::endl << std::endl;
		}
		std::cout << std::endl << std::endl;
	} while(temp != Fc);

	//std::cout << "==========" << std::endl;
	//std::cout << Fc << std::endl;
	//std::cout << "==========" << std::endl;


	// Step 3: Perform a right reduction of the remaining FDs in Fc, i.e., identify
	// and remove all attributes on the right-hand sides of FDs in Fc that are
	// extraneous


	//std::cout << "Step 3" << std::endl;

	do {
		Fc = temp;
		for(auto fd : Fc) { 
			std::cout << "For $" << fd.from << " \\ar " << fd.to << "$:" << std::endl;
			std::cout << "\\begin{itemize}" << std::endl;

			for(auto b : fd.to) {
				auto missingAttrib = fd.to - AttributeSet({b});

				auto testFc = (Fc - fd) + FD(fd.from, missingAttrib);

				auto closure = CalculateAttributeClosure(testFc, fd.from);

				std::cout << "\\item $CalculateAttributeClosure(" << texifyFDSet(testFc) << ", " << fd.from << ") = " << closure;

				if(closure.find(b) != closure.end()) {
					temp = testFc;
					std::cout << " \\supset " << b << "$, so $F_C=" << texifyFDSet(temp) << "$" << std::endl;
					//std::cout << "\\mincoverthree\t{" << fd.from << "}\t{" << fd.to << "}\t{" << b << "}\t{" << missingAttrib << "}\t{" << closure << "}\t{1}" << std::endl;
				} else {
					std::cout << " \\not \\supset " << b << "$, so do nothing" << std::endl;
					//std::cout << "\\mincoverthree\t{" << fd.from << "}\t{" << fd.to << "}\t{" << b << "}\t{" << missingAttrib << "}\t{" << closure << "}\t{0}" << std::endl;
				}
			}
			std::cout << "\\end{itemize}" << std::endl << std::endl;
		}
		std::cout << std::endl << std::endl;
	} while(temp != Fc);

	//std::cout << "==========" << std::endl;
	//std::cout << Fc << std::endl;
	//std::cout << "==========" << std::endl;

	// Step 4: Remove all FDs of the form A -> EmptySet from Fc, which have perhaps
	// been produced in the previous step, since they are meaningless
	for(auto fd : Fc) {
		if(fd.to == EmptySet) {
			temp.erase(fd);
		}
	}

	Fc = temp;

	return Fc;
}

FunctionalDependencySet CalculateMinimalCover(FunctionalDependencySet fds) {
	auto Fc = CalculateMinimalCoverIntermediate(fds);
	auto temp = Fc;

	// Step 5a: If the goal is to obtain a minimal cover in standard form,
	// decompose the right-hand sides of all FDs in Fc such that each
	// FD in Fc has a single attribute on its right-hand side
	for(auto fd : Fc) {
		if(fd.to.size() > 1) {
			auto decomposition = FDSet({});
			for(auto b : fd.to) {
				decomposition.insert(FD(fd.from, AttributeSet({b})));
			}
			temp = (temp - fd) + decomposition;
		}
	}

	Fc = temp;

	return Fc;
}

FunctionalDependencySet CalculateNonstandardMinimalCover(FunctionalDependencySet fds) {
	auto Fc = CalculateMinimalCoverIntermediate(fds);
	auto H = Fc;
	auto temp = H;
	Fc = FunctionalDependencySet({});

	// Step 5b: If the goal is to obtain a minimal cover in nonstandard form,
	// apply the union rule to all FDs with equal left-hand sides
	// H := F
	do {
		H = temp;
		for(auto fd : H) {
			auto G = FunctionalDependencySet({});
			auto X = AttributeSet();

			for(auto g : H) {
				if(fd.from == g.from) {
					G.insert(g);
					X = X + g.to;
				}
			}
			temp = H - G;
			Fc.insert(FD(fd.from, X));
		}
	} while(temp != H);

	return Fc;
}
