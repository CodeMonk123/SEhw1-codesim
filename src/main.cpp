#include <ASTParser.hpp>
#include <Detect.hpp>
#include <iomanip>
#include <clipp.h>
#include <Global.hpp>
#include <unistd.h>
#include <PrePorcess.hpp>
using namespace std;

bool verboseSet;

int main(int argc, char *argv[])
{
    string firstFile, secondFile;
    bool helpSet = false;
    verboseSet = false;
    auto cli = (
        clipp::value("input file1", firstFile),
        clipp::value("input file2", secondFile),
        clipp::option("-v", "--verbose").set(verboseSet).doc("verbose(show more details)").required(false),
        clipp::option("-h", "--help").set(helpSet).doc("help(guide how to use codesim)").required(false)
    );

    if(!clipp::parse(argc, argv, cli)) {
        cout << clipp::make_man_page(cli, argv[0]);
        return -1;
    }

    if(helpSet) {
        cout << clipp::make_man_page(cli, argv[0]);
        return 0;
    }
    
    string file1 = createTempFile(firstFile);
    string file2 = createTempFile(secondFile);
    ASTParser parser = ASTParser(file1);
    parser.parseTheAST();

    ASTParser parser2 = ASTParser(file2);
    parser2.parseTheAST();

    if (verboseSet)
    {
        cout << "First file:" << firstFile << endl;
        cout << "Second file:" << secondFile << endl;
        cout << "AST 1:" << endl;
        parser.root->outputASTNode();
        cout << "AST 2:" << endl;
        parser2.root->outputASTNode();
        cout << "Comparing two ASTs" << endl;
    }

    cout<< fixed << setprecision(2) << GreedyStringTiling(parser, parser2)  << endl;
    removeTempFile(file1);
    removeTempFile(file2);
    return 0;
}
