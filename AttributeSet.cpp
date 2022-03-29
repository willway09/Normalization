#include "AttributeSet.hpp"
#include <sstream>

AttributeSet::AttributeSet(std::string initStr) {
	for(auto attributeStr : initStr) {
		insert(attributeStr);
	}
}

std::ostream& operator<<(std::ostream& os, const AttributeSet& as) {
	for(auto attribute : as) {
		os << attribute;
	}
	return os;
}

bool operator<(const AttributeSet& x, const AttributeSet& y) {
	std::ostringstream xss;
	xss << x;
	std::string xs = xss.str();

	std::ostringstream yss;
	yss << y;
	std::string ys = yss.str();

	if(xs.length() < ys.length()) {
		return true;
	} else if(xs.length() == ys.length()) {
		return xs < ys;
	} else {
		return false;
	}
}
