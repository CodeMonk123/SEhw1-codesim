#include<ASTParser.hpp>

using namespace std;

int main() {
    string filename;
    cin >> filename;
    ASTParser parser = ASTParser(filename);
    parser.parseTheAST();
}