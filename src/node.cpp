#include "node.h"

bool operator<(const Node& node_1, const Node& node_2){
    if (node_1.x < node_2.x)        return true;
    else if (node_1.x > node_2.x)   return false;

    // if x is equal
    return (node_1.y < node_2.y);
}