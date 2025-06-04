#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Node
{
    int key;
    Node *parent{nullptr}, *child{nullptr};
    Node *prev{this}, *next{this};

    bool marked{false};
    int degree{0};

    Node(int key) : key(key) {}
};

class FibonacciHeap
{
    Node *min;
    int numNodes;

    void cutOut(Node *node)
    {
        if (node->parent == nullptr)
        {
            return;
        }

        auto parent = node->parent;

        if (node->next == node)
        {
            parent->child = nullptr;
        }
        else
        {
            if (parent->child == node)
            {
                parent->child = node->next;
            }

            node->next->prev = node->prev;
            node->prev->next = node->next;
        }

        parent->degree--;

        node->parent = nullptr;
        node->marked = false;

        min->next->prev = node;
        node->next = min->next;
        min->next = node;
        node->prev = min;

        if (parent->parent == nullptr)
        {
            return;
        }

        if (!parent->marked)
        {
            parent->marked = true;
        }
        else
        {
            cutOut(parent);
        };
    }

public:
    FibonacciHeap() : min(nullptr), numNodes(0)
    {
    }

    int getMin()
    {
        return min->key;
    }

    Node *insert(int key)
    {
        auto node = new Node(key);

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

        return node;
    }

    int extractMin()
    {
        if (min == nullptr)
            return -1;

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

        int minVal = min->key;

        if (min->next == min)
        {
            delete min;
            min = nullptr;
            numNodes--;
            return minVal;
        }

        auto newMin = min->next;
        min->next->prev = min->prev;
        min->prev->next = min->next;
        delete min;
        numNodes--;

        int maxDegree = floor(log2(numNodes)) + 1;
        std::vector<Node *> aux(maxDegree + 1, nullptr);

        auto currNode = newMin;

        if (numNodes == 0)
        {
            min = nullptr;
            return minVal;
        }

        min = currNode;
        auto startNode = currNode;

        do
        {
            auto nextNode = currNode->next;

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

            currNode = nextNode;
            if (newMin->key > currNode->key)
            {
                newMin = currNode;
            }
        } while (currNode != startNode);

        min = newMin;
        return minVal;
    }

    void decreaseKey(Node *node, int newKey)
    {
        if (newKey >= node->key)
        {
            return;
        }

        node->key = newKey;

        if (node->parent != nullptr && node->parent->key > newKey)
        {
            cutOut(node);
        }

        if (node->key < min->key)
        {
            min = node;
        }
    }
};

int main()
{
    return 0;
}