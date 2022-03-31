#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

class AttributeSet : public std::set<char> {
	public:
		AttributeSet(std::string initStr);
		AttributeSet() {

		}
		AttributeSet(std::vector<char>& attributes);

		std::set<AttributeSet> powerSetNoEmpty();

	private:
		friend std::ostream& operator<<(std::ostream& os, const AttributeSet& as);
		friend bool operator<(const AttributeSet& x, const AttributeSet& y);
		friend AttributeSet operator+(const AttributeSet& x, const AttributeSet& y);
		friend AttributeSet operator*(const AttributeSet& x, const AttributeSet& y);
};

std::ostream& operator<<(std::ostream& os, const std::set<AttributeSet>& asSet);
AttributeSet operator+(const AttributeSet& x, const AttributeSet& y);
AttributeSet operator-(const AttributeSet& x, const AttributeSet& y);
AttributeSet operator*(const AttributeSet& x, const AttributeSet& y);

typedef AttributeSet Relation;
