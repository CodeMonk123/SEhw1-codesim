CC = g++
CPPFLAGS = -g -std=c++11 -lclang
LLVM_INCLUDE = /usr/lib/llvm-10/include
LLVM_LIB = /usr/lib/llvm-10/lib
MESSAGE?=update

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
	./codesim ./testcase/1.cpp  ./testcase/1.format.cpp
	./codesim ./testcase/1.cpp  ./testcase/2.format.cpp 
	./codesim ./testcase/1.cpp  ./testcase/3.format.cpp 
	./codesim ./testcase/1.cpp  ./testcase/4.format.cpp 
	./codesim ./testcase/2.format.cpp ./testcase/3.format.cpp
	./codesim ./testcase/2.format.cpp ./testcase/4.format.cpp
	./codesim ./testcase/3.format.cpp ./testcase/4.format.cpp
	./codesim ./testcase/5.format.cpp ./testcase/6.format.cpp
	./codesim ./testcase/5.format.cpp ./testcase/7.format.cpp
	./codesim ./testcase/6.format.cpp ./testcase/7.format.cpp

	./codesim ./testcase/1.cpp  ./testcase/5.format.cpp 
	./codesim ./testcase/1.cpp  ./testcase/6.format.cpp 
	./codesim ./testcase/1.cpp  ./testcase/7.format.cpp  

push:
	git add .
	git commit -m "$(MESSAGE)"
	git push origin master
