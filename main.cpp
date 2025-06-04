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
    FibonacciHeap() : min(nullptr), numNodes(0) {}

    int getMin()
    {
        if (min == nullptr)
        {
            return -1;
        }

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

        std::vector<Node *> rootNodes;
        auto currNode = min->next;
        while (currNode != min)
        {
            rootNodes.push_back(currNode);
            currNode = currNode->next;
        }

        min->next->prev = min->prev;
        min->prev->next = min->next;
        delete min;
        numNodes--;

        if (numNodes == 0)
        {
            min = nullptr;
            return minVal;
        }

        int maxDegree = floor(log2(numNodes)) + 1;
        std::vector<Node *> aux(maxDegree + 1, nullptr);

        for (auto node : rootNodes)
        {
            int degree = node->degree;
            while (aux[degree] != nullptr)
            {
                auto other = aux[degree];
                if (node->key > other->key)
                {
                    std::swap(node, other);
                }

                other->next->prev = other->prev;
                other->prev->next = other->next;

                if (node->child == nullptr)
                {
                    node->child = other;
                    other->next = other->prev = other;
                }
                else
                {
                    auto firstChild = node->child;
                    auto lastChild = firstChild->prev;

                    lastChild->next = other;
                    other->prev = lastChild;
                    other->next = firstChild;
                    firstChild->prev = other;
                }

                other->parent = node;
                node->degree++;
                aux[degree] = nullptr;
                degree++;
            }

            aux[degree] = node;
        }

        min = nullptr;
        for (auto node : aux)
        {
            if (node != nullptr)
            {
                if (min == nullptr || node->key < min->key)
                {
                    min = node;
                }
            }
        }

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
    FibonacciHeap heap;

    std::cout << "=== Fibonacci Heap Demo ===" << std::endl;

    std::cout << "Inserting: 10, 5, 20, 3, 15" << std::endl;
    auto node5 = heap.insert(5);
    auto node10 = heap.insert(10);
    auto node3 = heap.insert(3);
    auto node20 = heap.insert(20);
    auto node15 = heap.insert(15);

    std::cout << "Min after inserts: " << heap.getMin() << std::endl;

    std::cout << "Extracting min: " << heap.extractMin() << std::endl;
    std::cout << "New min: " << heap.getMin() << std::endl;

    std::cout << "Decreasing key of node (15) to 1" << std::endl;
    heap.decreaseKey(node15, 1);
    std::cout << "Min after decrease: " << heap.getMin() << std::endl;

    std::cout << "Extracting all remaining:" << std::endl;
    while (heap.getMin() != -1)
    {
        std::cout << heap.extractMin() << " ";
    }
    std::cout << std::endl;

    std::cout << "=== Demo Complete ===" << std::endl;

    return 0;
}