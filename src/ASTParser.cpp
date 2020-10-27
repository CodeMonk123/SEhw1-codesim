#include <ASTParser.hpp>
#include <iostream>

using namespace std;
CXChildVisitResult visitor(CXCursor c, CXCursor parent, CXClientData clientData);

ostream &operator<<(ostream &stream, const CXString &str)
{
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}


void ASTParser::parseTheAST()
{
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        this->fileName.c_str(),
        nullptr,
        0,
        nullptr,
        0,
        CXTranslationUnit_None);

    if (unit == nullptr)
    {
        cerr << "Unable to parse translation unit. Aborting." << endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);

    clang_visitChildren(
        cursor,
        visitor,
        this);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}

// 把ASTParser当作ClientData传入
CXChildVisitResult visitor(CXCursor c, CXCursor parent, CXClientData clientData)
{ 
    // cout << cursor2String(c) << endl;
    ASTNode *newNode = new ASTNode(clang_getCursorKind(c));
    ASTParser* parser = (ASTParser*) clientData;
    if (clang_getCursorKind(parent) == CXCursor_TranslationUnit)
    {
        if(parser->verbose) {
            cout << "Parent: " << clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " | Children: " << clang_getCursorKindSpelling(clang_getCursorKind(c)) << endl;
        }
        parser->cursorNodeMap.insert(pair<unsigned, ASTNode *>(clang_hashCursor(c), newNode));
        newNode->setDepth(parser->root->getDepth() + 1);
        parser->root->addChild(newNode);
    }
    else
    {
        ASTNode *parentNode = parser->cursorNodeMap.at(clang_hashCursor(parent));
        newNode->setDepth(parentNode->getDepth() + 1);
        parser->cursorNodeMap.insert(pair<unsigned, ASTNode *>(clang_hashCursor(c), newNode));
        parentNode->addChild(newNode);
        if(parser->verbose) {
            cout << "Parent: " << clang_getCursorKindSpelling(clang_getCursorKind(parent)) << " | Children: " << clang_getCursorKindSpelling(clang_getCursorKind(c)) << endl;
        }
    }
    return CXChildVisit_Recurse;
}