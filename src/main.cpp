#include <ASTParser.hpp>
#include <ezOptionParser.hpp>
#include <Detect.hpp>
#include <iomanip>
using namespace std;

void Usage(ez::ezOptionParser &opt)
{
    std::string usage;
    opt.getUsage(usage);
    std::cout << usage;
};

// int main()
// {
//     string filename;
//     cin >> filename;
//     ASTParser parser = ASTParser(filename);
//     parser.parseTheAST();
// }

int main(int argc, const char *argv[])
{
    ez::ezOptionParser opt;
    opt.overview = "Codesim aims to find the similarity of two cpp/hpp files.";
    opt.syntax = "./codesim FIRST SECOND [OPTIONS]";
    opt.example = "./codesim A.cpp B.cpp --verbose\n";
    opt.footer = "Codesim 0.0.1, developed by CuiZihan\n";

    opt.add(
        "",
        0,
        0,
        0,
        "verbose (display runtime information)",
        "-v",
        "--verbose");

    opt.add(
        "",                            // Default.
        0,                             // Required?
        0,                             // Number of args expected.
        0,                             // Delimiter if expecting multiple args.
        "Display usage instructions.", // Help description.
        "-h",                          // Flag token.
        "-help",                       // Flag token.
        "--help",                      // Flag token.
        "--usage"                      // Flag token.
    );

    opt.parse(argc, argv);

    if (opt.isSet("-h"))
    {
        Usage(opt);
        return 0;
    }

    bool verboseSet = false;
    if (opt.isSet("-v"))
    {
        verboseSet = true;
        cout << "Verbose" << endl;
    } 

    string firstFile, secondFile;
    if (verboseSet && opt.firstArgs.size() != 3)
    {
        cerr << "ERROR: Expected 2 arguments. Given: " << opt.firstArgs.size() - 1 << endl;
        Usage(opt);
        return 0;
    }

    if (!verboseSet && argc != 3)
    {
        cerr << "ERROR: Expected 2 arguments. Given: " << argc - 1 << endl;
        Usage(opt);
        return 0;
    }

    firstFile = string(argv[1]);
    secondFile = string(argv[2]);

    if (verboseSet)
    {
        cout << "Analyzing: " << firstFile << " " << secondFile << endl;
        cout << "Building AST:" << endl;
    }

    ASTParser parser = ASTParser(firstFile, verboseSet);
    parser.parseTheAST();

    ASTParser parser2 = ASTParser(secondFile, verboseSet);
    parser2.parseTheAST();

    if (verboseSet)
    {
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
