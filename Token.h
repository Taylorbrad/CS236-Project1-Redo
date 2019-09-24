#pragma once
#include <iostream>
#include <stack>
using namespace std;

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EndOf};

class Token
{
    public:
        Token(TokenType inTokenType, stack <char> tokenFromScanner, int lineNum);
        string tokenToString();
        string tokenTypeToString();
        string toString();
        
    private:
        stack <char> token;
        TokenType tokenType;
        int lineNumOcurringOn;
    
};


