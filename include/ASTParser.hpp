#include <iostream>
#include <clang-c/Index.h>

using namespace std;

class ASTParser
{
private:
    string fileName;

public:
    ASTParser(string fileName)
    {
        this->fileName = fileName;
    }

    void parseTheAST();
};