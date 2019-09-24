#include "Scanner.h"
#include "Token.h"
#include <cctype>
using namespace std;

TokenType setTokenType(char inChar, char nextChar);
string charStackToString(stack <char> inCharStack);

Scanner::Scanner(string fileName)
{
    this->fileName = fileName;
}
void Scanner::tokenize()
{
    int lineNum = 1;
    int lineNumTemp = 0;
    ifstream inFile;
    ofstream outFile;
    char currentChar;
    char tempChar;
    stack <char> currentTokenStack;
    stack <char> emptyStack;
    stack <Token> allTokensInFile;
    TokenType tokenType;
    
    inFile.open(this->fileName);
    
    if(!inFile)
    {
        cout << "Unable to read file";
        return;
    }
    
    while (inFile.peek() != EOF) //While you have not yet reached the end of file, execute:
    {
        while(isspace(inFile.peek())) //Whenever the scanner encounters whitespace, iterate out until there is no more white space
        {
            if (inFile.peek() == '\n')
            {
                lineNum += 1;
            }
            inFile.get();
        }

        currentTokenStack = emptyStack; //Empty the stack to fill it with another token
        
        currentChar = inFile.get(); //get the next character
        tokenType = setTokenType(currentChar, inFile.peek());//set token types
        
        switch (tokenType)//compare token types
        {
            case COLON_DASH:
            {
                currentTokenStack.push(currentChar); //push the colon
                currentChar = inFile.get(); //get the dash, wait for the next push to get it on the stack
            }
            case UNDEFINED:
            {
                
            }
            case COMMA: //All single character tokens fall through to ADD case
            {
                
            }
            case PERIOD:
            {
                
            }
            case Q_MARK:
            {
                
            }
            case LEFT_PAREN:
            {
                
            }
            case RIGHT_PAREN:
            {
                
            }
            case COLON:
            {
                
            }
            case MULTIPLY:
            {
                
            }
            case ADD: //All single character tokens fall through to the following ADD case:
            {
                currentTokenStack.push(currentChar);
                break;
            }
            case SCHEMES:
            case FACTS:
            case RULES:
            case QUERIES:
            case ID:
            {
                while (isalnum(inFile.peek()))
                {
                    currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                }
                currentTokenStack.push(currentChar);
                if (charStackToString(currentTokenStack) == "Schemes")
                {
                    tokenType = SCHEMES;
                }
                else if (charStackToString(currentTokenStack) == "Facts")
                {
                    tokenType = FACTS;
                }
                else if (charStackToString(currentTokenStack) == "Rules")
                {
                    tokenType = RULES;
                }
                else if (charStackToString(currentTokenStack) == "Queries")
                {
                    tokenType = QUERIES;
                }
                break;
            }
            case STRING: // kinda works!
            {
                do
                {
                    
                    currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                    if (currentChar == '\n')
                    {
                        lineNumTemp += 1;
                    }
                    
                    if(inFile.peek() == '\'')
                    {
                        tempChar = inFile.get();
                        
                        if(inFile.peek() == '\'')
                        {
                            // cout << "do we even get here?";
                            inFile.putback(tempChar);
                            currentTokenStack.push(currentChar);
                            currentChar = inFile.get();
                            currentTokenStack.push(currentChar);
                            currentChar = inFile.get();
                            currentTokenStack.push(currentChar);
                            currentChar = inFile.get();
                            
                        }
                        else
                        {
                            inFile.putback(tempChar);
                        }
                        // cout << currentChar;
                    }
                } while (currentChar != '\'' /*&& currentChar != '\n'*/ && inFile.peek() != EOF/*inFile.peek() != '\'' && inFile.peek() != '\n' && inFile.peek() != EOF*/);
                

                currentTokenStack.push(currentChar);
                

                if (inFile.peek() == EOF)
                {
                    tokenType = setTokenType('&','a'); //set token type to UNDEFINED by passing random characters to setTokenType
                }
                break;
            }
            case COMMENT:
            {
                if (inFile.peek() == '|') //If you get a | as your character, push it, and get the #
                {
                    do
                        {
                            // cout << "|"; //IDK TBH
                            currentTokenStack.push(currentChar); //push the current character within the comment
                            currentChar = inFile.get(); //get the next character
                            if (currentChar == '\n')
                                {
                                    lineNumTemp += 1;
                                }
                        } while (currentChar != '#' && inFile.peek() != EOF);//Iterate until you find a | or EOF
                        currentTokenStack.push(currentChar);
                }
                else //if its a line comment, this else executes
                {
                    while (inFile.peek() != '\n' && inFile.peek() != EOF)
                    {
                        currentTokenStack.push(currentChar);
                        currentChar = inFile.get();
                    }
                    currentTokenStack.push(currentChar);
                }

                
            }// end COMMENT case
                
                break;
            
            case EndOf:
            {
                break;
            }
            default:
            {
                break;
            }
        }// end switch statement
        
        Token currentToken = Token(tokenType, currentTokenStack, lineNum); //Create the token object from the data collected
        allTokensInFile.push(currentToken); //push that token to the stack
        
        lineNum += lineNumTemp;
        lineNumTemp = 0;
        
        
    } // end while !eof loop
    
    
    inFile.close(); //Close the input file
    
    outFile.open("out_file_test.txt"); //Open the output file
    
    
    if (!outFile.is_open())
    {
        cout << "There was an issue trying to create the output text file :/\n";
        return;
    }
    
    stack <Token> reverseTokens;
    
    while (!allTokensInFile.empty())
    {
        reverseTokens.push(allTokensInFile.top());
        allTokensInFile.pop();
    }
    int tokenCounter = 0;
    while (!reverseTokens.empty())
    {//this is currently backwards
        tokenCounter += 1;
        Token writeToken = reverseTokens.top();
        outFile << writeToken.toString() << endl;
        reverseTokens.pop();
    }
    
    outFile << "Total Tokens = " << tokenCounter << endl;
    outFile.close();
    
} //end of Tokenize


TokenType setTokenType(char inChar, char nextChar)
{
    TokenType tokenTypeToReturn;
    
    if (inChar == ',')
    tokenTypeToReturn = COMMA;
    
    else if (inChar == '.')
    tokenTypeToReturn = PERIOD;
    
    else if (inChar == '?')
    tokenTypeToReturn = Q_MARK;
    
    else if (inChar == '(')
    tokenTypeToReturn = LEFT_PAREN;
    
    else if (inChar == ')')
    tokenTypeToReturn = RIGHT_PAREN;
    
    else if (inChar == ':' && nextChar != '-')
    tokenTypeToReturn = COLON;
    
    else if (inChar == ':' && nextChar == '-')
    tokenTypeToReturn = COLON_DASH;
    
    else if (inChar == '*')
    tokenTypeToReturn = MULTIPLY;
    
    else if (inChar == '+')
    tokenTypeToReturn = ADD;
    
    else if (isalpha(inChar))
    tokenTypeToReturn = ID;
    
    else if (inChar == '\'')
    tokenTypeToReturn = STRING;
    
    else if (inChar == '#')
    tokenTypeToReturn = COMMENT;
    
    else if (inChar == EOF)
    tokenTypeToReturn = EndOf;
    
    else
    tokenTypeToReturn = UNDEFINED;
    
    return tokenTypeToReturn;
}
string charStackToString(stack <char> inCharStack)
{
    string tempString = "";
    string stringToken = "";
    char tempTop;
    
    stack <char> temp = inCharStack; //save the token array so that it isnt destroyed in the process. In hindsight I may not have considered scope.
    
    while(!inCharStack.empty())
    {
        tempTop = inCharStack.top();
        stringToken = tempTop + stringToken;
        inCharStack.pop();
    }
    
    inCharStack = temp; //reload the token array to what it was

    return stringToken;
}
