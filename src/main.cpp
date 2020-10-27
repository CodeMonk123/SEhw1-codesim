#include<ASTParser.hpp>

using namespace std;

int main() {
    string filename;
    // cin >> filename;
    filename = "./test/testcase1.hpp";
    ASTParser parser = ASTParser(filename);
    parser.parseTheAST();
}