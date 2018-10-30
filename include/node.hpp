#pragma once

#include <vector>

enum node_type
{
    NONE
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
