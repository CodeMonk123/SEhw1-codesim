#include <ASTParser.hpp>
#include <ezOptionParser.hpp>
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
        cout << "verbose set true" << endl;
    }

    std::string firstFile, secondFile;
    if (opt.firstArgs.size() != 3)
    {
    std:
        cerr << "ERROR: Expected 2 arguments. Given" << opt.firstArgs.size() - 1 << endl;
        Usage(opt);
        return 0;
    }

    firstFile = *opt.firstArgs[1];
    secondFile = *opt.firstArgs[2];

    std::cout << "Analyze: " << firstFile << " " << secondFile << endl;
    return 0;
}
