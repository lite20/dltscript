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

    public:
        // ifstream to read file with
        std::ifstream inFile;

        // char to hold current char
        char c;

        // vector of tokens
        std::vector<std::string> tokens;

        // buffer for tokens being constructed
        std::stringstream token_buffer;

        // holds current line during parsing, and final
        // line count after
        int lines = 0;

        // buffer to hold data from file (1mb large)
        char buffer[BUFF_SIZE];

        // push a token to the token vector and clear string stream
        void push_token()
        {
            // std::cout << token_buffer.str().c_str() << " ";
            tokens.push_back(token_buffer.str());
            token_buffer.str(std::string());
        }

        // constructor parses given file
        full(char* file)
        {
            // set buffer for file and open file
            inFile.rdbuf()->pubsetbuf(buffer, BUFF_SIZE);
            inFile.open(file, std::ifstream::in);

            // check if file open was successful
            if(!inFile.is_open()) console::crash(1, "could not open file");

            // iterate over file character by character
            while (inFile.get(c))
            {
                // push if space or linebreak
                if (c == ' ' || c == ';') push_token();

                // increment if newline
                if (c == '\n') lines++;

                // check if is symbol/punctuation ()
                else if (ispunct(c))
                {
                    // check if last char holds placeholder character.
                    // this is really checking if this is the first symbol we've hit
                    // since parsing normal characters
                    if (last_char == ' ')
                    {
                        // get size of token that was being read
                        token_buffer.seekg(0, std::ios::end);
                        int size = token_buffer.tellg();

                        // if token was forming before hitting a symbol, push it
                        if (size > 0) push_token();

                        last_char = c;
                        token_buffer << c;
                    }
                    else
                    {
                        // if we don't have two identical symbols, or an = for the second
                        // then push the symbols independently
                        if (last_char != c && c != '=') push_token();

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
                    push_token();

                    token_buffer << c;
                }

                // add character to token buffer
                else token_buffer << c;
            }
        }
    };
}
