#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Node
{
    int key;
    Node *parent, *child;
    Node *prev, *next;

    bool marked{false};
    int degree;

    Node(int key) : key(key) {}
};

class FibonacciHeap
{
    Node *min;
    int numNodes;

public:
    FibonacciHeap() : min(nullptr), numNodes(0) {}
    FibonacciHeap(Node *min) : min(min), numNodes(1) {}

    Node *getMin()
    {
        return min;
    }

    void insert(Node *node)
    {
        if (min == nullptr)
        {
            min = node;
            node->prev = node->next = node;
        }
        else
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
        }

        numNodes++;
    }

    int extractMin()
    {
        if (min->child != nullptr)
        {
            auto firstChild = min->child;
            auto currChild = min->child;
            do
            {
                currChild->parent = nullptr;
                currChild->marked = false;
                currChild = currChild->next;
            } while (currChild != firstChild);

            auto nextChild = firstChild->prev;
            auto oldNext = min->next;

            min->next = firstChild;
            firstChild->prev = min;

            nextChild->next = oldNext;
            oldNext->prev = nextChild;
        }

        int maxDegree = floor(log2(numNodes)) + 1;
        std::vector<Node *> aux(maxDegree, nullptr);

        auto currNode = min->next;

        min->next->prev = min->prev;
        min->prev->next = min->next;

        int minVal = min->key;
        delete min;
        numNodes--;

        if (numNodes == 0)
        {
            min = nullptr;
            return minVal;
        }

        min = currNode;
        do
        {
            int degree = currNode->degree;
            if (aux[degree] == nullptr)
            {
                aux[degree] = currNode;
            }
            else
            {
                if (aux[degree]->key < currNode->key)
                {
                    currNode->next->prev = currNode->prev;
                    currNode->prev->next = currNode->next;

                    auto child = aux[degree]->child;
                    if (child != nullptr)
                    {
                        auto nextChild = child->next;
                        child->next = currNode;
                        currNode->prev = child;
                        nextChild->prev = currNode;
                        currNode->next = nextChild;
                    }
                    else
                    {
                        aux[degree]->child = currNode;
                    }

                    currNode->parent = aux[degree];

                    aux[degree]->degree++;
                    aux[degree + 1] = aux[degree];
                    aux[degree] = nullptr;
                }
                else
                {
                    aux[degree]->next->prev = aux[degree]->prev;
                    aux[degree]->prev->next = aux[degree]->next;

                    auto child = currNode->child;
                    if (child != nullptr)
                    {

                        auto nextChild = child->next;
                        child->next = aux[degree];
                        aux[degree]->prev = child;
                        nextChild->prev = aux[degree];
                        aux[degree]->next = nextChild;
                    }
                    else
                    {
                        currNode->child = aux[degree];
                    }

                    aux[degree]->parent = currNode;

                    currNode->degree++;
                    aux[degree + 1] = currNode;
                    aux[degree] = nullptr;
                }
            }

            currNode = currNode->next;
            if (min->key > currNode->key)
            {
                min = currNode;
            }
        } while (currNode != min);

        return minVal;
    }
};

int main()
{
    std::shared_ptr min = std::make_shared<Node>(1);
    return 0;
}