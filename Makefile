CC = g++
CPPFLAGS = -g -std=c++11 -lclang
LLVM_INCLUDE = /usr/lib/llvm-10/include
LLVM_LIB = /usr/lib/llvm-10/lib

codesim: clean ast-parser
	$(CC) -o codesim AST.o ASTParser.o src/main.cpp -I ./include -I ./lib/include  -I $(LLVM_INCLUDE) -L $(LLVM_LIB) $(CPPFLAGS)

ast-parser: 
	$(CC) -c src/AST.cpp src/ASTParser.cpp  -I ./include -I ./lib/include -I $(LLVM_INCLUDE) -L $(LLVM_LIB) $(CPPFLAGS)



.PHONY: clean test push

clean:
	rm -f *.o
	rm -f *~
	rm -f codesim

test: codesim
	./codesim ./test/testcase1.hpp ./test/testcase2.hpp -v

push:
	git add .
	git commit -m"update"
	git push origin master
