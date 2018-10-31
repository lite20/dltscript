#pragma once

#include <vector>

#include "tokenizer.hpp"

namespace
{
    enum node_type
    {
        PRIMITIVE, OPERATION, FUNCTION_CALL, DECLARATION
    };

    struct node
    {
        node_type type;

        std::vector<node*> subnodes;

        node(node_type t)
        {
            type = t;
        }
    };

    class abstract_syntax_tree
    {
    public:
        node* root_node;

        abstract_syntax_tree(std::vector<tokenizer::token>& tokens)
        {
            root_node = new node(PRIMITIVE);
            
        }
    };
}
