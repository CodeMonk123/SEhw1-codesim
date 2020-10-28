#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> removeHeaders(vector<string> lines)
{
    vector<string> result;
    for (int i = 0; i < lines.size(); i++)
    {
        string compressedLine = lines[i];
        compressedLine.erase(remove(compressedLine.begin(), compressedLine.end(), ' '), compressedLine.end());
        if (compressedLine.substr(0, 1) != "#")
        {
            result.push_back(lines[i]);
        }
    }
    return result;
}

string createTempFile(string fileName)
{
    ifstream fin;
    fin.open(fileName);
    vector<string> lines;

    string line;
    while (getline(fin, line))
    {
        lines.push_back(line);
    }
    fin.close();

    vector<string> newLines = removeHeaders(lines);

    string tempFileName = tmpnam(nullptr);
    tempFileName = tempFileName + ".cpp";
    if (verboseSet)
    {
        cout << "Make temp file: " << tempFileName << endl;
    }
    ofstream fout(tempFileName);
    for (int i = 0; i < newLines.size(); i++)
    {
        fout << newLines[i] << endl;
    }
    fout.close();
    return tempFileName;
}

bool removeTempFile(string tempFileName)
{
    if (remove(tempFileName.c_str()) == 0)
    {
        if (verboseSet)
        {
            cout << "Remove temp file: " << tempFileName << endl;
        }
        return true;
    }
    return false;
}