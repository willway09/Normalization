#pragma once
#include "FunctionalDependencySet.hpp"

FunctionalDependencySet CalculateFDClosure(FunctionalDependencySet fds, Relation R) {

	FDSet fdsplus = fds;

	//Don't bootstrap by adding that each attribute functionally determines itself
	for(auto attribute : R) {
		fdsplus.insert(FD(attribute, attribute));
	}

	FDSet fdsplusold = fdsplus;

	while(true) {
		FDSet temp = fdsplus;
		for(auto f : fdsplus) {
			auto fromImp = f.from.powerSetNoEmpty();

			for(auto fi : fromImp) {
				temp.insert(FD(f.from, fi));
			}

			auto toImp = f.to.powerSetNoEmpty();

			for(auto fi : toImp) {
				temp.insert(FD(f.to, fi));
			}
			
		}

		fdsplus = temp;

		auto attribPS = R.powerSetNoEmpty();
		for(auto f : fdsplus) {
			for(auto s : attribPS) {
				temp.insert(FD(f.from + s, f.to + s));
			}
		}

		fdsplus = temp;

		for(auto f1 = fdsplus.begin(); f1 != fdsplus.end(); ++f1) {
			for(auto f2 = fdsplus.begin(); f2 != fdsplus.end(); ++f2) {
				if(f1 == f2) continue; //Same entry

				if(f1->to == f2->from) {
					temp.insert(FD(f1->from,f2->to));
				}
			}
		}
	
		if(fdsplus == fdsplusold) break;
		fdsplusold = fdsplus;
	}

	return fdsplus;
}
