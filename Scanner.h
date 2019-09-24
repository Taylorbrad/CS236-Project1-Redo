#pragma once //only compile this file once
#include <stack>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class Scanner
{
    public:
        Scanner(string inFile);
        void tokenize();
        
    private:
        stack <char> tokenTemp;
        ifstream inFile;
        string fileName;
};