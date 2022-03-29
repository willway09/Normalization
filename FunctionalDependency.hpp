#pragma once
#include <iostream>
#include <string>

#include "AttributeSet.hpp"

class FunctionalDependency {
	public:
		FunctionalDependency(std::string initStr);
	private:
		AttributeSet from;
		AttributeSet to;
		friend std::ostream& operator<<(std::ostream& os, const FunctionalDependency& fd);
		friend bool operator<(const FunctionalDependency& x, const FunctionalDependency& y);
};

typedef FunctionalDependency FD;
