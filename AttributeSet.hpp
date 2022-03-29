#pragma once
#include <iostream>
#include <string>
#include <set>

class AttributeSet : public std::set<char> {
	public:
		AttributeSet(std::string initStr);
		AttributeSet() {

		}

	private:
		friend std::ostream& operator<<(std::ostream& os, const AttributeSet& as);
		friend bool operator<(const AttributeSet& x, const AttributeSet& y);
};
