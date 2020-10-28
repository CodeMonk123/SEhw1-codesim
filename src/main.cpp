#include <ASTParser.hpp>
#include <Detect.hpp>
#include <iomanip>
#include <clipp.h>
#include <Global.hpp>
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
    

    ASTParser parser = ASTParser(firstFile);
    parser.parseTheAST();

    ASTParser parser2 = ASTParser(secondFile);
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

    vector<string> seq1 = parser.root->tranverse();
    vector<string> seq2 = parser2.root->tranverse();

    if(verboseSet) 
    {
        cout << "Generating sequence 1: "<<seq1[0] <<" "<<seq1[1] <<"..."  <<endl;
        cout << "Generating sequence 2: " << seq2[0]<<" "<<seq2[1] << "..." <<endl;
    }

    cout<< fixed << setprecision(2) << GreedyStringTiling(seq1, seq2) << "%" << endl;
    return 0;
}
