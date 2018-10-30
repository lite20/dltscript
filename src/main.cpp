#include <cstdio>
#include <string>

#include "node.hpp"
#include "tokenizer.hpp"
#include "console.hpp"

int main(int argc, char** argv)
{
    std::vector<node*> nodes;

    tokenizer::full* tok = new tokenizer::full(argv[0]);

    return 0;
}
