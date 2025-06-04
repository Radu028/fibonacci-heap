#include <iostream>
#include <memory>

struct Node
{
    int key;
    Node *parent;
    Node *child;
    Node *prev, *next;

    bool marked{false};
    int degree;

    Node(int key) : key(key) {}
    Node(int key, Node *parent) : key(key), parent(parent) {}
    Node(int key, Node *parent, Node *prev,
         Node *next)
        : key(key), parent(parent), prev(prev), next(next) {}
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
        auto nextMinNode = min->next;

        min->next = node;
        node->prev = min;
        nextMinNode->prev = node;
        node->next = nextMinNode;

        if (min->key > node->key)
        {
            min = node;
        }

        node->degree = 0;
        node->marked = false;
        node->prev = node->next = node;

        numNodes++;
    }

    int extractMin()
    {
        if (min->child != nullptr)
        {
            auto prevChild = min->child;
            auto currChild = min->child;
            do
            {
                currChild->parent = nullptr;
                currChild->marked = false;
                currChild = currChild->next;
            } while (currChild != prevChild);

            auto nextChild = prevChild->prev;
            auto oldNext = min->next;

            min->next = prevChild;
            prevChild->prev = min;

            nextChild->next = oldNext;
            oldNext->prev = nextChild;
        }

        int maxDegree = floor(log2(numNodes)) + 1;
        std::vector<Node *> aux(maxDegree, nullptr);
    }
};

int main()
{
    std::shared_ptr min = std::make_shared<Node>(1);
    return 0;
}