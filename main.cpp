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

class FibonacciHeap
{
    std::shared_ptr<Node> min;

public:
    void setMin(std::shared_ptr<Node> &min)
    {
        this->min = min;
    }

    std::shared_ptr<Node> getMin()
    {
        return min;
    }

    void insert(std::shared_ptr<Node> node)
    {
        std::shared_ptr<Node> leftNode{min};
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
    }
};

int main()
{
    std::shared_ptr min = std::make_shared<Node>(1);
    return 0;
}