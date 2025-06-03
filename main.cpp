#include <iostream>
#include <memory>

struct Node
{
    int key;
    Node *parent;
    Node *child;
    Node *left, *right;

    bool marked{false};
    int degree;

    Node(int key) : key(key) {}
    Node(int key, Node *parent) : key(key), parent(parent) {}
    Node(int key, Node *parent, Node *left,
         Node *right)
        : key(key), parent(parent), left(left), right(right) {}
};

class FibonacciHeap
{
    Node *min;
    int numNodes;

public:
    FibonacciHeap(Node *min) : min(min), numNodes(1) {}

    Node *getMin()
    {
        return min;
    }

    void insert(Node *node)
    {
        Node *leftNode{min};
        while (leftNode->right != nullptr)
        {
            leftNode = leftNode->right;
        }

        leftNode->right = node;
        node->left = leftNode;

        if (min->key > node->key)
        {
            min = node;
        }

        node->degree = 0;
        node->marked = false;

        numNodes++;
    }

    int extractMin()
    {
        if (min->child != nullptr)
        {
            auto rightestParent = min;
            while (rightestParent->right != nullptr)
            {
                rightestParent = rightestParent->right;
            }

            auto leftestChild = min->child;
            while (leftestChild->left != nullptr)
            {
                leftestChild = leftestChild->left;
            }

            rightestParent->right = leftestChild;
            leftestChild->left = rightestParent;

            auto child = leftestChild;
            do
            {
                child->parent = nullptr;
                child->marked = false;
            } while (child->right != nullptr);
        }

        int maxDegree = floor(log2(numNodes)) + 1;
    }
};

int main()
{
    std::shared_ptr min = std::make_shared<Node>(1);
    return 0;
}