#include <iostream>
#include <clang-c/Index.h>
#include <clang-c/Platform.h>
#include <vector>
#include <map>
#include <AST.hpp>

using namespace std;

class ASTParser
{
private:
    string fileName;
public:
    ASTParser(string fileName, bool verbose)
    {
        this->fileName = fileName;
        this->verbose = verbose;
        root = new ASTNode(CXCursor_TranslationUnit);
        root->setDepth(0);
    }
    void parseTheAST();
    ASTNode* root;
    map<unsigned, ASTNode*> cursorNodeMap;
    bool verbose;
};
