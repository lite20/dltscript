#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "console.hpp"

#define BUFF_SIZE 1000000

namespace tokenizer
{
    class full
    {
    private:
        // holds last symbol or ' '
        char last_char = ' ';

        // avoid blanks by tracking how much we've put in token_buffer
        int buffered = 0;

        // buffer to hold data from file (1mb large)
        char buffer[BUFF_SIZE];

        // char to hold current char
        char c;

    public:
        // ifstream to read file with
        std::ifstream inFile;

        // vector of tokens
        std::vector<std::string> tokens;

        // buffer for tokens being constructed
        std::stringstream token_buffer;

        // holds current line during parsing, and final
        // line count after
        int lines = 0;

    private:
        // push a token to the token vector and clear string stream
        void push_token()
        {
            if (buffered == 0)
            {
                // buffered will have 1 added so -1
                buffered = -1;
                return;
            }

            tokens.push_back(token_buffer.str());
            token_buffer.str(std::string());

            // buffered will have 1 added so -1
            buffered = -1;
        }

        bool twoPartOperator()
        {
            // all double symbols are operators or nothing
            if (last_char == c) return true;

            // equality operators end in =
            else if (c == '=') return true;

            // pipe operators
            else if (last_char == '|' && c == '>') return true;

            // arrow operators
            else if (last_char == '-' && c == '>') return true;

            else return false;
        }

        // check if current character is a symbol never used
        // in the double operators
        bool isAlwaysSingleCharOp()
        {
            if (c == '#') return true;

            else if (c == ':') return true;
            else if (c == '{') return true;
            else if (c == '}') return true;
            else if (c == '(') return true;
            else if (c == ')') return true;
            else if (c == '[') return true;
            else if (c == ']') return true;
            else if (c == ',') return true;

            else return false;
        }

    public:
        // constructor parses given file
        full(const char* file)
        {
            // set buffer for file and open file
            inFile.rdbuf()->pubsetbuf(buffer, BUFF_SIZE);
            inFile.open(file, std::ifstream::in);

            // check if file open was successful
            if(!inFile.is_open()) console::crash(1, "could not open file");

            // iterate over file character by character
            while (inFile.get(c))
            {
                // push current token buffer if space or linebreak
                if (c == ' ') push_token();

                // increment if newline
                else if (c == '\n')
                {
                    push_token();
                    lines++;
                }

                // put the single character operators alone
                else if (isAlwaysSingleCharOp())
                {
                    push_token();
                    token_buffer << c;
                    push_token();
                }

                // check if is symbol/punctuation ()
                else if (ispunct(c) && c != '_')
                {
                    // check if last char holds placeholder character.
                    // this is really checking if this is the first symbol we've hit
                    // since parsing normal characters
                    if (last_char == ' ')
                    {
                        // if token was forming before hitting a symbol, push it
                        if (buffered > 0) push_token();

                        // force buffer to 0 to account for the new token we're adding.
                        // normally we only do 1 push per loop but in this case
                        // we've flushed the previous and are adding anew that may be
                        // pushed next loop (but would cause buffered = 0 so it'd be ignored)
                        // while this is a bit of a hack, if the explanation is insufficient,
                        // remove it, step through the code, and see what happens. There large
                        // definetely cleaner ways of organizing this.
                        buffered = 0;

                        last_char = c;
                        token_buffer << c;
                    }
                    else
                    {
                        // if we don't have two identical symbols, or an = for the second
                        // then push the symbols independently
                        if (!twoPartOperator()) push_token();

                        // push whatever remains (either both or singular symbol)
                        token_buffer << c;
                        push_token();

                        // reset last char flag/variable
                        last_char = ' ';
                    }
                }

                // last token was symbol but now folled by normal char
                else if (last_char != ' ')
                {
                    // reset last char flag/variable
                    last_char = ' ';

                    push_token();

                    token_buffer << c;
                }

                // add character to token buffer
                else token_buffer << c;

                // increment tally of buffered characters
                buffered++;
            }
        }
    };
}
