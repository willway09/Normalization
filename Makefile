all: main

normalization.a: main
	ar ru normalization.a *.o

main: FunctionalDependency.o AttributeSet.o FunctionalDependencySet.o CalculateFDClosure.hpp CalculateAttributeClosure.hpp CalculateMinimalCover.hpp
	g++ -g -std=c++17 -o main main.cpp FunctionalDependency.o AttributeSet.o FunctionalDependencySet.o

FunctionalDependency.o: FunctionalDependency.cpp FunctionalDependency.hpp
	g++ -g -std=c++17 -c -o FunctionalDependency.o FunctionalDependency.cpp

AttributeSet.o: AttributeSet.cpp AttributeSet.hpp
	g++ -g -std=c++17 -c -o AttributeSet.o AttributeSet.cpp

FunctionalDependencySet.o: FunctionalDependencySet.cpp FunctionalDependencySet.hpp
	g++ -g -std=c++17 -c -o FunctionalDependencySet.o FunctionalDependencySet.cpp

website: web.cpp main
	@-mkdir html
	#em++ -g -std=c++17 -o html/web.html web.cpp FunctionalDependency.cpp AttributeSet.cpp FunctionalDependencySet.cpp
	#em++ -g -std=c++17 -o web.js web.cpp FunctionalDependency.cpp AttributeSet.cpp FunctionalDependencySet.cpp
	em++ -g -std=c++17 -o web/web.html web.cpp FunctionalDependency.cpp AttributeSet.cpp FunctionalDependencySet.cpp \
		-s EXPORTED_FUNCTIONS=_CalculateAllCandidateKeysWebWrapper,_CalculateAttributeClosureWebWrapper,_CalculateFDClosureWebWrapper,_CalculateMinimalCoverWebWrapper\
		-s EXPORTED_RUNTIME_METHODS=ccall,cwrap
output: main
	./main
	pdflatex output.tex
	

clean:
	@-rm main AttributeSet.o FunctionalDependency.o
	@-rm chaseout.tex
	@-rm output.aux output.log output.pdf
