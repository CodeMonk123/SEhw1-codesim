#include "ASTParser.hpp"
#include "Detect.hpp"
#include <iomanip>
#include "clipp.h"
#include "Logger.hpp"
using namespace std;

bool Logger::verbose;

int main(int argc, char *argv[])
{
    string firstFile, secondFile;
    bool helpSet = false;
    bool verboseSet = false;
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

    Logger::verbose = verboseSet;

    Logger::info("First file:", firstFile, "\n");
    Logger::info("Second file:", secondFile, "\n");

    
    ASTParser parser = ASTParser(firstFile);
    parser.parseTheAST();
    Logger::info("AST1: ", "\n");
    parser.root->outputASTNode();

    ASTParser parser2 = ASTParser(secondFile);
    parser2.parseTheAST();
    Logger::info("AST2: ", "\n");
    parser2.root->outputASTNode();
    
    Logger::info("Comparing two ASTs", "\n");
    cout<< fixed << setprecision(2) << GreedyStringTiling(parser, parser2)  << endl;
    return 0;
}
