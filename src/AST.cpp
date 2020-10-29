#include "AST.hpp"
#include "Logger.hpp"
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
        Logger::info("  ");
    }
    Logger::info("--|",kindName,"\n"); 
    for(int i = 0; i < children.size(); i++) {
        children[i]->outputASTNode();
    }
    
}

vector<string> ASTNode::tranverse() {
    vector<string> result;
    result.push_back(this->kindName);
    for(auto p=this->children.begin(); p != this->children.end(); p++) {
        vector<string> temp = (*p)->tranverse();
        result.insert(result.end(), temp.begin(), temp.end());
    }
    return result;
}
