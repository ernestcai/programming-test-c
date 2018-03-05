#ifndef PROGRAMMING_TEST_C_NODE_H
#define PROGRAMMING_TEST_C_NODE_H


// Node represent holes only
struct Node{
    long x;          // the vertical line (0->top)
    long y;          // the horizontal line (0->left)
};


bool operator<(const Node& node_1, const Node& node_2);

#endif //PROGRAMMING_TEST_C_NODE_H
