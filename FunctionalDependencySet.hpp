#pragma once

#include <set>
#include <iostream>
#include <sstream>
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

std::string texifyFDSet(FDSet f) {

	std::string rtn = "\\set{";
	int counter = 0;
	for(auto s : f) {
		std::ostringstream fromss, toss;
		fromss << s.from;
		toss << s.to;

		auto from = fromss.str();
		auto to = toss.str();

		if(from == "") from = "\\varnothing";
		if(to == "") to = "\\varnothing";

		rtn += from + " \\ar " + to;
		if(counter != f.size() - 1) {
			rtn += ", ";
		}
		counter++;
	} rtn += "}";
	return rtn;
}
