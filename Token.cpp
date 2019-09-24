#include "Token.h"

using namespace std;

Token::Token(TokenType inTokenType, stack <char> tokenFromScanner, int lineNum)
{
    this->token = tokenFromScanner;
    this->tokenType = inTokenType;
    this->lineNumOcurringOn = lineNum;
}
string Token::tokenToString()
{
    string tempToken = "";
    string stringToken = "";
    char tempTop;
    
    stack <char> temp = this->token; //save the token array so that it isnt destroyed in the process. In hindsight I may not have considered scope.
    
    while(!this->token.empty())
    {
        tempTop = this->token.top();
        stringToken = tempTop + stringToken;
        token.pop();
    }
    
    this->token = temp; //reload the token array to what it was

    return stringToken;
    
}
string Token::tokenTypeToString()
{
    switch(this->tokenType)
    {
        case COMMA:
        {
            return "COMMA"; 
            break;
        }
        case PERIOD:
        {
            return "PERIOD"; 
            break;
        }
        case Q_MARK:
        {
            return "Q_MARK"; 
            break;
        }
        case LEFT_PAREN:
        {
            return "LEFT_PAREN"; 
            break;
        }
        case RIGHT_PAREN:
        {
            return "RIGHT_PAREN"; 
            break;
        }
        case COLON:
        {
            return "COLON"; 
            break;
        }
        case COLON_DASH:
        {
            return "COLON_DASH"; 
            break;
        }
        case MULTIPLY:
        {
            return "MULTIPLY"; 
            break;
        }
        case ADD:
        {
            return "ADD"; 
            break;
        }
        case SCHEMES:
        {
            return "SCHEMES"; 
            break;
        }
        case FACTS:
        {
            return "FACTS"; 
            break;
        }case RULES:
        {
            return "RULES"; 
            break;
        }
        case QUERIES:
        {
            return "QUERIES"; 
            break;
        }
        case ID:
        {
            return "ID"; 
            break;
        }
        case STRING:
        {
            return "STRING"; 
            break;
        }
        case COMMENT:
        {
            return "COMMENT"; 
            break;
        }
        case UNDEFINED:
        {
            return "UNDEFINED"; 
            break;
        }
        case EndOf:
        {
            return "EOF"; 
            break;
        }
    }
    return "Error";
}
string Token::toString()
{
    string tokenLine = "(" + tokenTypeToString() + ",\"" + tokenToString() + "\"," + to_string(this->lineNumOcurringOn) + ")";
    return tokenLine;
}