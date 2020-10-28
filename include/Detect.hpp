#pragma once
#include <vector>
#include <iostream>
#include "Global.hpp"
#include "ASTParser.hpp"
using namespace std;

const int MIN_MATCH_LENGTH = 5;


struct match
{
    int index1;
    int index2;
    int length;
    match(int index1, int index2, int length) : index1(index1), index2(index2), length(length) {}
};

double GreedyStringTiling(const ASTParser& ast1, const ASTParser& ast2)
{
    vector<string> p = ast1.root->tranverse();
    vector<string> t = ast2.root->tranverse();

    if(verboseSet) 
    {
        cout << "Generating sequence 1" << "..." <<endl;
        cout << "Generating sequence 2" << "..." <<endl;
    }

    if (p.size() > t.size())
    {
        vector<string> temp = p;
        p = t;
        t = temp;
    }
    int lengthP = p.size();
    int lengthT = t.size();
    bool *markP = new bool[lengthP];
    bool *markT = new bool[lengthT];

    for (int i = 0; i < lengthP; i++)
    {
        markP[i] = false;
    }

    for (int i = 0; i < lengthT; i++)
    {
        markT[i] = false;
    }

    vector<match> tiles;

    int maxMatch = MIN_MATCH_LENGTH;

    do
    {
        maxMatch = MIN_MATCH_LENGTH;
        vector<match> matches;
        for (int i = 0; i < lengthP; i++)
        {
            for (int j = 0; j < lengthT; j++)
            {
                int commonSubStringLength = 0;
                while (true)
                {
                    int index1 = i + commonSubStringLength;
                    int index2 = j + commonSubStringLength;
                    if (index1 < lengthP && index2 < lengthT && !markP[index1] && !markT[index2] && p[index1] == t[index2])
                    {
                        commonSubStringLength++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (commonSubStringLength == maxMatch)
                {
                    match m(i, j, commonSubStringLength);
                    matches.push_back(m);
                }
                else if(commonSubStringLength > maxMatch)
                {
                    matches.erase(matches.begin(), matches.end());
                    match m(i, j, commonSubStringLength);
                    matches.push_back(m);
                    maxMatch = commonSubStringLength;
                }

            }
        }
        for(auto m = matches.begin(); m != matches.end(); m++) {
            for(int i = 0; i < (*m).length; i++) {
                markP[(*m).index1] = true;
                markT[(*m).index2] = true;
            }

            tiles.push_back(match((*m).index1, (*m).index2, (*m).length));
        }
    } while (maxMatch > MIN_MATCH_LENGTH);

    int matchLength = 0;

    // FIXME: 对于交叠的tiles，应该只计算一次
    for(int i = 0; i < tiles.size(); i++) {
        bool isAvailable = true;
        for(int j = 0; j < i; j++) {
            if(tiles[j].index1 < tiles[i].index1 && tiles[j].index1 + tiles[j].length > tiles[i].index1) {
                isAvailable = false;
                break;
            }
        }
        if(isAvailable) {
            if(verboseSet) {
                cout << "Find am avaliable tile: (" << tiles[i].index1 << ", " << tiles[i].index2 << ", " << tiles[i].length << ")" <<endl;
            }
            matchLength += tiles[i].length;
        }
    }

    return 100.0 * 2.0 * (double)matchLength / ((double)lengthP + (double)lengthT);
}