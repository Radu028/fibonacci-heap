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

    Node(int key) : key(key) {}
    Node(int key, std::shared_ptr<Node> &parent) : key(key), parent(parent) {}
    Node(int key, std::shared_ptr<Node> &parent, std::shared_ptr<Node> &left,
         std::shared_ptr<Node> &right)
        : key(key), parent(parent), left(left), right(right) {}
};

int main()
{
    std::shared_ptr min = std::make_shared<Node>(1);
    return 0;
}