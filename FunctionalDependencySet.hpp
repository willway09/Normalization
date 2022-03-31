#pragma once

#include <set>
#include <iostream>
#include <vector>

#include "FunctionalDependency.hpp"

class FunctionalDependencySet : public std::set<FunctionalDependency> {
	public:
		FunctionalDependencySet(const std::vector<FunctionalDependency>& fds);
		friend std::ostream& operator<<(std::ostream& os, const FunctionalDependencySet& fds);
		friend FunctionalDependencySet operator-(const FunctionalDependencySet& x, const FunctionalDependencySet& y);
		friend FunctionalDependencySet operator+(const FunctionalDependencySet& x, const FunctionalDependencySet& y);
};

FunctionalDependencySet operator-(const FunctionalDependencySet& x, const FunctionalDependencySet& y);
FunctionalDependencySet operator-(const FunctionalDependencySet& fds, const FunctionalDependency& fd);
FunctionalDependencySet operator+(const FunctionalDependencySet& fds, const FunctionalDependency& fd);
FunctionalDependencySet operator+(const FunctionalDependencySet& x, const FunctionalDependencySet& y);

typedef FunctionalDependencySet FDSet;
typedef FunctionalDependencySet FDS;
