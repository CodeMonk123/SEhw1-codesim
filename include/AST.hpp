#include <iostream>
#include <clang-c/Index.h>
#include <vector>
using namespace std;

class ASTNode {
private:
    CXCursorKind nodeKind;
    string kindName;
    vector<ASTNode*> children;
    int depth;
public:
    CXCursorKind getNodeKind();
    string getKindName();
    int getDepth();
    void setDepth(int);
    void addChild(ASTNode* node);
    ASTNode(CXCursorKind kind) {
        this->nodeKind = kind;
        this->kindName = clang_getCString(clang_getCursorKindSpelling(kind));
        this->children = vector<ASTNode*>();
        // cout << "new node: " << this->kindName << endl;
    }

    void outputASTNode();

};

class AST {
private:
    ASTNode* root;
public:
    AST(ASTNode*& root){
        this->root = root;
    }

    void outputAST();
};