#include "FunctionalDependency.hpp"
#include <cstring>

FunctionalDependency::FunctionalDependency(std::string initStr) {
	std::string first = initStr.substr(0, initStr.find("->"));
	std::string second = initStr.substr(initStr.find("->") + 2, initStr.length());
	from = AttributeSet(first);
	to = AttributeSet(second);
}

FunctionalDependency::FunctionalDependency(AttributeSet from, AttributeSet to) {
	this->from = from;
	this->to = to;
}

FunctionalDependency::FunctionalDependency(char from, char to) {
	this->from = AttributeSet(std::string(1, from));
	this->to = AttributeSet(std::string(1, to));
}

std::ostream& operator<<(std::ostream& os, const FunctionalDependency& fd) {
	os << fd.from << "->" << fd.to;
	return os;
}

bool operator<(const FunctionalDependency& x, const FunctionalDependency& y) {
	if(x.from < y.from) {
		return true;
	} else if(x.from == y.from) {
		return x.to < y.to;
	} else {
		return false;
	}
}

bool operator==(const FunctionalDependency& x, const FunctionalDependency& y) {
	return (x.from == y.from) && (x.to == y.to);
}
