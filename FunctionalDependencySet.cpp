#include "FunctionalDependencySet.hpp"

FunctionalDependencySet::FunctionalDependencySet(const std::vector<FunctionalDependency>& fds) {
	for(auto fd : fds) {
		insert(fd);
	}
}

std::ostream& operator<<(std::ostream& os, const FunctionalDependencySet& fds) {
	for(auto fd : fds) {
		os << fd << " ";
	}
	return os;
}
