#include "FunctionalDependencySet.hpp"
#include <algorithm>

FunctionalDependencySet::FunctionalDependencySet(const std::vector<FunctionalDependency>& fds) {
	for(auto fd : fds) {
		insert(fd);
	}
}

std::ostream& operator<<(std::ostream& os, const FunctionalDependencySet& fds) {
	int counter = 0;
	for(auto fd : fds) {
		os << fd << " ";
		counter++;
		if(counter > 5) {
			std::cout << std::endl;
			counter = 0;
		}
	}
	return os;
}

FunctionalDependencySet operator-(const FunctionalDependencySet& x, const FunctionalDependencySet& y) {
	FunctionalDependencySet rtn({});

	std::set_difference(x.begin(), x.end(), y.begin(), y.end(), std::inserter(rtn, rtn.end()));

	return rtn;
}

FunctionalDependencySet operator+(const FunctionalDependencySet& x, const FunctionalDependencySet& y) {
	FunctionalDependencySet rtn = x;

	rtn.insert(y.begin(), y.end());

	return rtn;
}

FunctionalDependencySet operator-(const FunctionalDependencySet& fds, const FunctionalDependency& fd) {
	FDSet rtn = fds;
	rtn.erase(fd);
	return rtn;
}

FunctionalDependencySet operator+(const FunctionalDependencySet& fds, const FunctionalDependency& fd) {
	FDSet rtn = fds;
	rtn.insert(fd);
	return rtn;
}
