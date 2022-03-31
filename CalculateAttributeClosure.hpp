#pragma once
#include "FunctionalDependencySet.hpp"

AttributeSet CalculateAttributeClosure(FunctionalDependencySet fds, AttributeSet A) {
	auto Aplus = A;
	auto Aplusold = Aplus;

	do {
		Aplusold = Aplus;
		for(auto fd : fds) {
			if(std::includes(Aplus.begin(), Aplus.end(), fd.from.begin(), fd.from.end())) {
				Aplus = Aplus + fd.to;
			}
		}

	} while(Aplusold != Aplus);

	return Aplus;
}
