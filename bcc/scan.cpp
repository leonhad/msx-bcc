#include "scan.h"
#include <iostream>

using namespace std;
using namespace definitions;

namespace bc
{

    Scan::Scan(string filein)
    {
        this->filein = new fstream(filein.c_str(), ios::in | ios::out);
        lineno = 0;
        reservedWords["IF"] = IF;
        reservedWords["THEN"] = THEN;
        reservedWords["ELSE"] = ELSE;
        reservedWords["FOR"] = FOR;
        reservedWords["TO"] = TO;
        reservedWords["NEXT"] = NEXT;
        reservedWords["DIM"] = DIM;
        reservedWords["END"] = END;
        reservedWords["PRINT"] = PRINT;
    }

    Scan::~Scan()
    {
        if (filein)
        {
            if (filein->is_open())
            {
                filein->close();
            }
            delete filein;
        }
    }

    char Scan::getNextChar()
    {
        int ret = EOF;
        if (!filein->eof())
        {
            ret = filein->get();
            if (ret == '\n')
            {
                lineno++;
            }
            else if (ret == '\r')
            {
                // Ignore CR
                return getNextChar();
            }
            current = ret;
        }
        return ret;
    }

    TokenType Scan::reservedLookup(string s)
    {
        map<string, TokenType>::iterator i;
        for (i = reservedWords.begin(); i != reservedWords.end(); i++)
        {
            if (s == (*i).first)
            {
                return (*i).second;
            }
        }
        return ID;
    }

    TokenType Scan::getSpecialChar(char c)
    {
        TokenType currentToken = ERROR;
        switch (c)
        {
        case EOF:
            currentToken = ENDFILE;
            break;
        case '=':
            currentToken = EQ;
            break;
        case '<':
            currentToken = LT;
            break;
        case '>':
            currentToken = GT;
            break;
        case '+':
            currentToken = PLUS;
            break;
        case '-':
            currentToken = MINUS;
            break;
        case '*':
            currentToken = TIMES;
            break;
        case '/':
            currentToken = OVER;
            break;
        case '(':
            currentToken = LPAREN;
            break;
        case ')':
            currentToken = RPAREN;
            break;
        case '[':
            currentToken = LBRACET;
            break;
        case ']':
            currentToken = RBRACET;
            break;
        case ',':
            currentToken = COMMA;
            break;
        case ';':
            currentToken = SEMI;
            break;
        case '\n':
            currentToken = ENDLINE;
            break;
        case ':':
            currentToken = ENDCOMMAND;
            break;
        case '$':
            currentToken = DOLLAR;
            break;
        default:
            break;
        }
        return currentToken;
    }

    TokenType Scan::getToken()
    {
        tokenString.erase();
        /* holds the current token to be returned */
        TokenType currentToken{};
        /* the current state always begins at START */
        StateType state = START;
        /* flag to indicate save to tokenString */
        while (state != DONE)
        {
            const int c = getNextChar();
            bool save = true;
            switch (state)
            {
            case START:
                if (isdigit(c))
                {
                    state = INNUM;
                }
                else if (isalpha(c))
                {
                    state = INID;
                }
                else if ((c == ' ') || (c == '\t'))
                {
                    save = false;
                }
                else if (c == '"')
                {
                    save = false;
                    state = INSTRING;
                }
                else
                {
                    state = DONE;
                    save = false;
                    currentToken = getSpecialChar(c);
                }
                break;
            case INNUM:
                if (!isdigit(c))
                {
                    /* backup in the input */
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID:
                switch (c)
                {
                case ' ':
                case '\t':
                    ungetNextChar();
                    save = false;
                    state = DONE;
                    currentToken = ID;
                    break;
                default:
                    TokenType temp = getSpecialChar(c);
                    switch (temp)
                    {
                    case ERROR:
                        break;
                    case ENDFILE:
                    default:
                        ungetNextChar();
                        save = false;
                        state = DONE;
                        currentToken = ID;
                        break;
                    }
                }
                break;
            case INSTRING:
                if (c == '"')
                {
                    save = false;
                    state = DONE;
                    currentToken = STRING;
                }
                break;
            case DONE:
                break;
            default:
                /* should never happen */
                cerr << "Scanner Bug: state= " << state << endl;
                state = DONE;
                currentToken = ERROR;
                break;
            }
            if (save)
            {
                tokenString += (char)c;
            }
            if (state == DONE)
            {
                if (currentToken == ID)
                {
                    currentToken = reservedLookup(tokenString);
                }
            }
        }
        return currentToken;
    }

    void Scan::ungetNextChar()
    {
        if (!filein->eof())
        {
            filein->putback(current);
        }
        if (current == '\n')
        {
            lineno--;
        }
    }

    unsigned int Scan::getLineno()
    {
        return lineno;
    }
} // namespace bc
