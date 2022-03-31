#include <iostream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <vector>

#include "FunctionalDependency.hpp"
#include "FunctionalDependencySet.hpp"

#include "CalculateFDClosure.hpp"
#include "CalculateAttributeClosure.hpp"
#include "CalculateMinimalCover.hpp"
#include "CalculateAllCandidateKeys.hpp"

int main() {
	Relation R("ABCDEF");

	FDSet S({FD("DF->C"), FD("BC->F"), FD("E->A"), FD("ABC->E")});

	auto res = CalculateAllCandidateKeys(R, S);

	std::cout << res;
}

AttributeSet parseAttributeSet(std::string as_string) {
	as_string.erase(std::remove(as_string.begin(), as_string.end(), ' '), as_string.end());
	as_string.erase(std::remove(as_string.begin(), as_string.end(), ','), as_string.end());

	return AttributeSet(as_string);
}

FDSet parseFDSet(std::string fdsstring) {
	FDSet rtn({});
	fdsstring.erase(std::remove(fdsstring.begin(), fdsstring.end(), ' '), fdsstring.end());

	std::stringstream tokenize(fdsstring);

	std::string temp;

	std::vector<std::string> tokens;

	while(std::getline(tokenize, temp, ',')) {
		tokens.push_back(temp);
	}

	for(auto i : tokens) {
		rtn.insert(FD(i));
	}

	return rtn;
}

std::string CalculateAllCandidateKeysOutputString;

std::string CalculateAttributeClosureOutputString;

std::string CalculateFDClosureOutputString;

std::string CalculateMinimalCoverOutputString;

//2 `FunctionalDependencySet CalculateFDClosure(FunctioanlDependencySet fds)`
//3 `AttributeSet CalculateAttributeClosure(FunctioanlDependencySet fds, AttributeSet as)`
//4 `FunctioanlDependencySet CalculateMinimalCover(FunctioanlDependencySet fds)`
//5 `CalculateAllCandidateKeys(AttributeSet as, FunctioanlDependencySet fds)`

extern "C" {

const char* CalculateAllCandidateKeysWebWrapper(const char* as_string, const char* fdsstring) {
	Relation R = parseAttributeSet(as_string);
	FDSet fds = parseFDSet(fdsstring);

	auto result = CalculateAllCandidateKeys(R, fds);

	std::ostringstream out;
	out << result;
	out.flush();

	CalculateAllCandidateKeysOutputString = out.str();
	return CalculateAllCandidateKeysOutputString.c_str();
}

const char* CalculateAttributeClosureWebWrapper(const char* as_string, const char* fdsstring) {
	AttributeSet as = parseAttributeSet(as_string);
	FDSet fds = parseFDSet(fdsstring);

	auto result = CalculateAttributeClosure(fds, as);

	std::ostringstream out;
	out << result;
	out.flush();
	
	CalculateAttributeClosureOutputString = out.str();
	return CalculateAttributeClosureOutputString.c_str();
}

const char* CalculateFDClosureWebWrapper(const char* as_string, const char* fdsstring) {
	Relation R = parseAttributeSet(as_string);
	FDSet fds = parseFDSet(fdsstring);

	auto result = CalculateFDClosure(fds, R);

	std::ostringstream out;
	out << result;
	out.flush();
	
	CalculateFDClosureOutputString = out.str();
	return CalculateFDClosureOutputString.c_str();
}

const char* CalculateMinimalCoverWebWrapper(const char* as_string, const char* fdsstring) {
	Relation R = parseAttributeSet(as_string);
	FDSet fds = parseFDSet(fdsstring);

	auto result = CalculateMinimalCover(fds);

	std::ostringstream out;
	out << result;
	out.flush();
	
	CalculateMinimalCoverOutputString = out.str();
	return CalculateMinimalCoverOutputString.c_str();
}

}
