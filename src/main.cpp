#include <cstdio>
#include <string>

#include "node.hpp"
#include "tokenizer.hpp"
#include "console.hpp"

int main(int argc, char** argv)
{
    // vector to hold nodes
    std::vector<node*> nodes;

    // check paramter count
    if (argc != 1) console::crash(1, "invalid paramaters. Usage: dsc <file>");

    // tokenize root document
    tokenizer::full* tok = new tokenizer::full(argv[0]);

    return 0;
}
