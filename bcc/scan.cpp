#include "scan.h"
#include <iostream>

using namespace std;

namespace bc
{
    Scan::Scan(const string &filein) : filein{filein.c_str(), ios::in | ios::out}
    {
        current = EOF;
        lineno = 0;
        reserved_words["IF"] = IF;
        reserved_words["THEN"] = THEN;
        reserved_words["ELSE"] = ELSE;
        reserved_words["FOR"] = FOR;
        reserved_words["TO"] = TO;
        reserved_words["NEXT"] = NEXT;
        reserved_words["DIM"] = DIM;
        reserved_words["END"] = END;
        reserved_words["PRINT"] = PRINT;
    }

    Scan::~Scan()
    {
        if (filein)
        {
            if (filein.is_open())
            {
                filein.close();
            }
        }
    }

    char Scan::next_char()
    {
        int ret = EOF;
        if (!filein.eof())
        {
            ret = filein.get();
            if (ret == '\n')
            {
                lineno++;
            }
            else if (ret == '\r')
            {
                // Ignore CR
                return next_char();
            }

            current = ret;
        }

        return static_cast<char>(ret);
    }

    TokenType Scan::reserved_lookup(const string &name)
    {
        for (const auto &[key, value] : reserved_words)
        {
            if (name == key)
            {
                return value;
            }
        }
        return ID;
    }

    TokenType Scan::get_special_char(const char check_char)
    {
        TokenType currentToken = ERROR;
        switch (check_char)
        {
        case EOF:
            currentToken = END_FILE;
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
            currentToken = END_LINE;
            break;
        case ':':
            currentToken = END_COMMAND;
            break;
        case '$':
            currentToken = DOLLAR;
            break;
        default:
            break;
        }
        return currentToken;
    }

    TokenType Scan::next_token()
    {
        token_string.erase();
        /* holds the current token to be returned */
        TokenType currentToken{};
        /* the current state always begins at START */
        StateType state = START;
        /* flag to indicate save to token_string */
        while (state != DONE)
        {
            const char c = next_char();
            bool save = true;
            switch (state)
            {
            case START:
                if (isdigit(c))
                {
                    state = IN_NUMBER;
                }
                else if (isalpha(c))
                {
                    state = IN_ID;
                }
                else if ((c == ' ') || (c == '\t'))
                {
                    save = false;
                }
                else if (c == '"')
                {
                    save = false;
                    state = IN_STRING;
                }
                else
                {
                    state = DONE;
                    save = false;
                    currentToken = get_special_char(c);
                }
                break;
            case IN_NUMBER:
                if (!isdigit(c))
                {
                    /* backup in the input */
                    unget_char();
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case IN_ID:
                switch (c)
                {
                case ' ':
                case '\t':
                    unget_char();
                    save = false;
                    state = DONE;
                    currentToken = ID;
                    break;
                default:
                    TokenType temp = get_special_char(c);
                    switch (temp)
                    {
                    case ERROR:
                        break;
                    case END_FILE:
                    default:
                        unget_char();
                        save = false;
                        state = DONE;
                        currentToken = ID;
                        break;
                    }
                }
                break;
            case IN_STRING:
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
                token_string += (char)c;
            }

            if (state == DONE)
            {
                if (currentToken == ID)
                {
                    currentToken = reserved_lookup(token_string);
                }
            }
        }
        return currentToken;
    }

    void Scan::unget_char()
    {
        if (!filein.eof())
        {
            filein.putback(static_cast<char>(current));
        }
        if (current == '\n')
        {
            lineno--;
        }
    }

    unsigned int Scan::current_line_number() const
    {
        return lineno;
    }
}
