#include "Scanner.h"
#include "Token.h"
#include <cctype>
using namespace std;

char returnIfIsAlpha(char inChar);
TokenType setTokenType(char inChar, char nextChar);
string charStackToString(stack <char> inCharStack);

Scanner::Scanner(string fileName)
{
    this->fileName = fileName;
}
void Scanner::tokenize()
{
    int lineNum = 1;
    // int badCreateFlag = 0;
    // int tempTrackerDebug = 0; 
    ifstream inFile;
    ofstream outFile;
    char currentChar;
    stack <char> currentTokenStack;
    stack <char> emptyStack;
    stack <Token> allTokensInFile;
    TokenType tokenType;
    
    // currentChar = inFile.peek();
    // char test = currentChar;
    // currentChar = test;
    inFile.open(this->fileName);
    
    if(!inFile)
    {
        cout << "Unable to read file";
        return;
    }
    
    while (inFile.peek() != EOF) //you gotta get all the tokens in this while statement
    {
        while(isspace(inFile.peek())) //Whenever the scanner encounters whitespace, iterate out until there is no more white space
        {
            if (inFile.peek() == '\n')
            {
                lineNum += 1;
            }
            inFile.get();
        }
        // badCreateFlag = 0; delete
        currentTokenStack = emptyStack; //Empty the stack to fill it with another token
        
        currentChar = inFile.get(); //get the next character
    
        
        tokenType = setTokenType(currentChar, inFile.peek());//set token types
        //old comment : if current character is one of the single character tokens, create the token object and move to the next token in file. Otherwise, keep scanning
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
            case ADD: //All single character tokens fall through to this case:
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
                while (isalnum(/*inFile.peek()*/currentChar))
                {
                    if (inFile.peek() == '\n')
                        {
                            lineNum += 1;
                        }
                    currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                }
                // currentTokenStack.push(currentChar); testing this without these 2 lines
                // currentChar = inFile.get();
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
                    tokenType = FACTS;
                }
                else if (charStackToString(currentTokenStack) == "Queries")
                {
                    tokenType = QUERIES;
                }
                // if (inFile.peek() == '\n')
                // {
                //     lineNum += 1;
                // }
                break;
            }
            case STRING: // kinda works! but eats the next character every time
            {
                
                while (/*currentChar != '\'' && */inFile.peek() != '\'' && inFile.peek() != '\n' && inFile.peek() != EOF)
                {
                    // cout << currentChar;
                    currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                }
                if (inFile.peek() == '\n')
                {
                    lineNum += 1;
                }
                // currentTokenStack.push(currentChar);
                // currentChar = inFile.get();
                cout<< currentChar;
                currentTokenStack.push(currentChar);
                currentChar = inFile.get();
                break;
            }
            case COMMENT:
            {
                if (inFile.peek() == '|') //If you get a | as your character, push it, and get the #
                {
                    // currentTokenStack.push(currentChar); //push the |
                    // currentChar = inFile.get(); //get the #
                    while (inFile.peek() != '#' && inFile.peek() != EOF)//Iterate until you find a | or EOF
                        {
                            // cout << "|"; //IDK TBH
                            currentTokenStack.push(currentChar); //push the current character within the comment
                            currentChar = inFile.get(); //get the next character
                            if (currentChar == '\n')
                                {
                                    lineNum += 1;
                                }
                        }
                }
                else //if its a line comment, this else executes
                {
                    while (inFile.peek() != '\n' && inFile.peek() != EOF)
                    {
                        // cout << "nLine";
                        currentTokenStack.push(currentChar);
                        currentChar = inFile.get();
                    }
                }
                if (inFile.peek() == '\n')
                {
                    lineNum += 1;
                }
                
            }// end COMMENT case
                
                break;
            // }
            
            case EndOf:
            {
                
                break;
            }
            default:
            {
                break;
            }
        }// end switch statement
        // if (badCreateFlag == 1) //this shouldnt be necessary anymore
        // {
            Token currentToken = Token(tokenType, currentTokenStack, lineNum); //Create the token object from the data collected
            allTokensInFile.push(currentToken); //push that token to the stack
        // }
        
        
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

char returnIfIsAlpha(char inChar)
{
    if (isalpha(inChar))
    {
        return inChar;
    }
    else
    {
        return '`'; //If the ` character is ever input, it will roast the code sort of I think maybe maybe not though because of the while loop.
    }
}
/*char returnIfIsAlNum(char inChar) //might not need this
{
    return 'a';
}*/
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


//old switch thing
/*switch (currentChar) //you gotta create the full token in this switch statement
        {
            case ',': //if current character is one of the single character tokens, create the token object and move to the next token in file. Otherwise, keep scanning
                if (currentChar == ',')
                tokenType = COMMA;
                
            case '.':
                if (currentChar == '.')
                tokenType = PERIOD;
                
            case '?':
                if (currentChar == '?')
                tokenType = Q_MARK;
                
            case '(':
                if (currentChar == '(')
                tokenType = LEFT_PAREN;
                
            case ')':
                if (currentChar == ')')
                tokenType = RIGHT_PAREN;
                
            case ':':
                if (currentChar == ':')
                tokenType = COLON;
                
            case '*':
                if (currentChar == '*')
                tokenType = MULTIPLY;
                
            case '+':
                if (currentChar == '+')
                tokenType = ADD;
                
                badCreateFlag = 1;
                currentTokenStack.push(currentChar);
            break; 
            
            case returnIfIsAlpha(currentChar): //If the character is alphabetic, take this case which will complete the token.
            {
                badCreateFlag = 1;
                while (isalnum(currentChar)) //While current character is an alphanumeric, push character to the token stack and iterate to the end of the token.
                {
                    currentTokenStack.push(currentChar);
                    currentChar = inFile.get();
                }
                break;
            }
            
            // break; //Break for multiple character tokens
            default:
                tempTrackerDebug += 1;
                cout << "+" << tempTrackerDebug;
                    // cout << "newlineees";
                badCreateFlag = 1;
                tokenType = UNDEFINED;
                currentTokenStack.push(currentChar);
            break;
        }*/