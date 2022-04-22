#pragma once
#include "FunctionalDependencySet.hpp"

#include <map>
#include <iostream>

/*
\[
\begin{matrix}
A & B & C & D & E & F \\
a & b & c & d_1 & e_1 & f_1 \\
a & b_2 & c_2 & d & e_2 & f_2 \\
a_3 & b_3 & c_3 & d & e & f_3 \\
a_4 & b_4 & c & d_4 & e & f \\
\end{matrix}
\]
*/

bool validRow(std::vector<int>& row) {
		bool validDecomposition = true;
		for(auto j : row) {
			if(j != 0) validDecomposition = false;
		}

		if(validDecomposition) {
			return true;
		}
		return false;
}

void writeMatrix(std::ostream& texOut, Relation& R, std::vector<std::vector<int>>& matrix, std::map<char, int> attrMap) {
	texOut << "\\[" << std::endl << "\\begin{matrix}" << std::endl;

	int i = 0;
	for(auto attr : R) {
		texOut << attr;
		if(i == R.size() - 1) {
			texOut << " \\\\" << std::endl;
		} else {
			texOut << " & ";
		}
		i++;
	}

	for(auto row : matrix) {
		int i = 0;

		bool vr = validRow(row);

		for(auto attr : R) {
			if(vr) texOut << "\\underline{";
			texOut << (char)(attr | 32);
			if(row[i] != 0) {
				texOut << "_" << row[i];
			}
			if(vr) texOut << "}";
			if(i == R.size() - 1) {
				texOut << " \\\\" << std::endl;
			} else {
				texOut << " & ";
			}
			i++;
		}
	}

	texOut << "\\end{matrix}" << std::endl << "\\]" << std::endl << std::endl;
}

void writeFD(std::ostream& texOut, const FD& fd) {
	texOut << "Apply $" << fd.from << " \\rightarrow " << fd.to << "$" << std::endl << std::endl;
}


bool ChaseTest(Relation R, std::vector<Relation> decomposition, FunctionalDependencySet fds, std::ostream* texOut = nullptr) {
	bool writeTex = (texOut != nullptr);

	std::vector<std::vector<int>> matrix;

	int row = 1;
	for(auto Rn : decomposition) {
		std::vector<int> rowVec;
		for(auto attr : R) {
			if(Rn.find(attr) != Rn.end()) {
				rowVec.push_back(0);
			} else {
				rowVec.push_back(row);
			}
		}
		row++;
		matrix.push_back(rowVec);
	}

	std::map<char, int> attrMap;

	int col = 0;
	for(auto attr : R) {
		attrMap[attr] = col;
		col++;
	}

	auto before = matrix;

	if(writeTex) {
		*texOut << "The initial matrix" << std::endl << std::endl;
		writeMatrix(*texOut, R, matrix, attrMap);
	}

	do {
		before = matrix;
		for(auto& fd : fds) {
			auto beforeFD = matrix;
			for(auto& row1 : matrix) {
				for(auto row2 : matrix) {
					//Compute if attributes match
					bool matches = true;
					for(auto attr : fd.from) {
						if(row1[attrMap[attr]] != row2[attrMap[attr]]) {
							matches = false;
							break;
						}
					}

					if(matches) {
						for(auto attr : fd.to) {
							int min = std::min(row1[attrMap[attr]], row2[attrMap[attr]]);
							row1[attrMap[attr]] = min;
							row2[attrMap[attr]] = min;
						}
					}
				}
			}

			writeFD(*texOut, fd);

			if(beforeFD != matrix) {
				writeMatrix(*texOut, R, matrix, attrMap);
			} else {
				*texOut << "Could not be applied" << std::endl << std::endl;
			}

			for(auto i : matrix) {
				if(validRow(i)) return true;
			}

		}
	} while(matrix != before);

	for(auto i : matrix) {
		if(validRow(i)) return true;
	}

	return false;
}
