#pragma once
#include "FunctionalDependencySet.hpp"

std::set<AttributeSet> CalculateAllCandidateKeys(Relation R, FunctionalDependencySet fds) {
	std::set<AttributeSet> rtn;

	AttributeSet allFrom;
	AttributeSet allTo;

	for(auto fd : fds) {
		allFrom.insert(fd.from.begin(), fd.from.end());
		allTo.insert(fd.to.begin(), fd.to.end());
	}

	// Step 1: Determine the attributes that are neither on the left side nor on the
	// right side of any FD.
	auto neitherSide = (R - allFrom - allTo);

	// Step 2: Determine the attributes that are only on the left side of any FD.
	auto leftSideOnly = allFrom - allTo;

	// Step 3: Determine the attributes that are only on the right side of any FD.
	auto rightSideOnly = allTo - allFrom;

	// Step 4: Combine the attributes from steps 1 and 2.
	auto mustInclude = neitherSide + leftSideOnly;

	// Step 5: Compute the closure of the attributes from step 4. If the attribute
	// closure is equal to all attributes of R, then the attributes from step4
	// form the only candidate key, and the algorithm terminates.
	if(CalculateAttributeClosure(fds, mustInclude) == R) {
		rtn.insert(mustInclude);
		return rtn;
	}

	// Step 6: Otherwise, determine the attributes that are included neither in
	// step 3 nor in step 4.
	auto bothSides = allTo * allFrom;

	// Step 7: Compute the closure of the attributes from step 4 (if there are any)
	// and every combination of attributes from step 6, and determine
	// those minimal attribute closures that are equal to R.
	auto attributeCombinations = bothSides.powerSetNoEmpty();

	for(auto as : attributeCombinations) {
		auto test = mustInclude + as;
		if(CalculateAttributeClosure(fds, test) == R) {
			bool superkey = false;
			for(auto known : rtn) {
				if(std::includes(test.begin(), test.end(), known.begin(), known.end())) {
					superkey = true;
					break;
				}
			}
			if(!superkey) {
				rtn.insert(test);	
			}
		}
	}

	return rtn;
}
