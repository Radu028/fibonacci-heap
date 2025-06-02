#include <iostream>
#include <memory>

struct Node
{
    int key;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> child;
    std::shared_ptr<Node> left, right;

    bool marked{false};
    int degree;
};