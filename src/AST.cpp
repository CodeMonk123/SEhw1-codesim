#include <AST.hpp>
using namespace std;

string ASTNode::getKindName() {
    return this->kindName;
}

CXCursorKind ASTNode::getNodeKind() {
    return this->nodeKind;
}

void ASTNode::addChild(ASTNode* node) {
    //cout << "add child "<< node->kindName << " to" << this->kindName <<  endl;
    this->children.push_back(node);
    //cout << this->kindName << "has " << this->children.size() << " children now." << endl;
}

void ASTNode::setDepth(int depth) {
    this->depth = depth;
}

int ASTNode::getDepth() {
    return this->depth;
}

void ASTNode::outputASTNode() {
    
    for(int i = 0; i < depth - 1; i++) {
        cout <<"  ";
    }
    cout <<"--|"<<kindName<< endl;
    for(int i = 0; i < children.size(); i++) {
        children[i]->outputASTNode();
    }
    
}

void AST::outputAST() {
    root->outputASTNode();
}
