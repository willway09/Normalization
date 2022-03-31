#include "AttributeSet.hpp"
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

AttributeSet::AttributeSet(std::string initStr) {
	for(auto attributeStr : initStr) {
		insert(attributeStr);
	}
}

std::set<AttributeSet> AttributeSet::powerSetNoEmpty() {
	std::vector<char> attributes;
	for(auto attribute : *this) {
		attributes.push_back(attribute);
	}

	std::set<AttributeSet> rtn;

	for(int i = 0; i < std::pow(2, attributes.size()); i++) {
		if(i == 0) continue;

		AttributeSet add;

		for(int j = 0; j < attributes.size(); j++) {
			if(i & (1 << j)) {
				add.insert(attributes[j]);
			}
		}
		rtn.insert(add);
	}

	return rtn;
}


AttributeSet::AttributeSet(std::vector<char>& attributes) {
	for(auto attribute : attributes) {
		insert(attribute);
	}
}

std::ostream& operator<<(std::ostream& os, const AttributeSet& as) {
	for(auto attribute : as) {
		os << attribute;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<AttributeSet>& asSet) {
	for(auto as : asSet) {
		os << as << std::endl;
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


AttributeSet operator+(const AttributeSet& x, const AttributeSet& y) {
	AttributeSet rtn = x;

	rtn.insert(y.begin(), y.end());

	return rtn;
}

AttributeSet operator-(const AttributeSet& x, const AttributeSet& y) {
	AttributeSet rtn;

	std::set_difference(x.begin(), x.end(), y.begin(), y.end(), std::inserter(rtn, rtn.end()));

	return rtn;
}

AttributeSet operator*(const AttributeSet& x, const AttributeSet& y) {
	AttributeSet rtn;

	std::set_intersection(x.begin(), x.end(), y.begin(), y.end(), std::inserter(rtn, rtn.end()));

	return rtn;
}
