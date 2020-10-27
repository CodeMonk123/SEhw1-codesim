#include <ASTParser.hpp>

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
        cursor, [](CXCursor c, CXCursor parent, CXClientData data) {
            cout << "Cursor kind:" << clang_getCursorSpelling(c) << " of kind " << clang_getCursorKindSpelling(clang_getCursorKind(c)) << endl;
            cout << "Parent is " << clang_getCursorSpelling(parent) << " of kind " << clang_getCursorKindSpelling(clang_getCursorKind(parent)) << endl;
            return CXChildVisit_Recurse;
        },
        nullptr);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}