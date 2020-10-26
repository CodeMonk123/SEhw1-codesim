CC = g++
CFLAGS = -g -std=c++11 -lclang
LLVM_INCLUDE = /usr/lib/llvm-10/include
LLVM_LIB = /usr/lib/llvm-10/lib

codesim: clean
	$(CC) -o codesim src/main.cpp -I $(LLVM_INCLUDE) -L $(LLVM_LIB) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f *~
	rm -f codesim