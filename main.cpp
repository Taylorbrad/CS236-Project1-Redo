//main.cpp
#include <iostream> //cin/cout
#include <fstream> //read/write files
#include <cctype> //isspace, isalpha, isalnum
#include <stack>
#include "Scanner.h"
// #include "Scanner.cpp"
#include "Token.h"
// #include "Token.cpp"

using namespace std;

int main(int, char* argv[])
{
    Scanner myFunScanner = Scanner(argv[1]);
    myFunScanner.tokenize();
    
    return 0;
}