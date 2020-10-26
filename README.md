- 编译方式
``` shell
g++  -I /usr/lib/llvm-10/include -L /usr/lib/llvm-10/lib -g -std=c++11 test.cpp -lclang -o test
```