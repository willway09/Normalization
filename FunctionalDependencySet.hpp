#pragma once

#include <set>
#include <iostream>
#include <vector>

#include "FunctionalDependency.hpp"

class FunctionalDependencySet : public std::set<FunctionalDependency> {
	public:
		FunctionalDependencySet(const std::vector<FunctionalDependency>& fds);
		friend std::ostream& operator<<(std::ostream& os, const FunctionalDependencySet& fds);
};

typedef FunctionalDependencySet FDSet;
typedef FunctionalDependencySet FDS;
