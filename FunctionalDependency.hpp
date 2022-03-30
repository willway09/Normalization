#pragma once
#include <iostream>
#include <string>

#include "AttributeSet.hpp"

class FunctionalDependency {
	public:
		FunctionalDependency(std::string initStr);
		FunctionalDependency(AttributeSet from, AttributeSet to);
		FunctionalDependency(char from, char to); //Unrigorous way to add a standalone attribute as a singleton AttributeSets
		AttributeSet from;
		AttributeSet to;
	private:
		friend std::ostream& operator<<(std::ostream& os, const FunctionalDependency& fd);
		friend bool operator<(const FunctionalDependency& x, const FunctionalDependency& y);
		friend bool operator==(const FunctionalDependency& x, const FunctionalDependency& y);
};

typedef FunctionalDependency FD;
