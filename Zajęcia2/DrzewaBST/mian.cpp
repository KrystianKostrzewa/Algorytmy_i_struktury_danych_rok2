#include <iostream>

using namespace std;

class BSTNode
{
public:
    int key;
    BSTNode* Left;
    BSTNode* Right;
    BSTNode* Parent;

    static BSTNode* Insert(BSTNode* node, int key);
    static void printTreePreOrder(BSTNode* node);
    static void printTreePostOrder(BSTNode* node);
    static void printTreeInOrder(BSTNode* node);

    static BSTNode* min(BSTNode* root);
    static BSTNode* max(BSTNode* root);

    static BSTNode* inOrderSuccessor(BSTNode* n);
    static BSTNode* inOrderPredeccessor(BSTNode* n);

};

BSTNode* BSTNode::Insert(BSTNode* node, int key)
{

    if (node == NULL)
    {
        node = new BSTNode;
        node->key = key;
        node->Left = NULL;
        node->Right = NULL;
        node->Parent = NULL;
    }
    else if (node->key < key) {
        node->Right = Insert(node->Right, key);
        node->Right->Parent = node;
    }
    else
    {
        node->Left = Insert(node->Left, key);
        node->Left->Parent = node;
    }

    return node;

}

static void printTreePreOrder(BSTNode* node) // task 1a
{
    cout << node->key << " ";
    if (node->Left != NULL)printTreePreOrder(node->Left);
    if (node->Right != NULL) printTreePreOrder(node->Right);
}

static void printTreePostOrder(BSTNode* node)//task 1b
{
    if (node->Left != NULL)printTreePostOrder(node->Left);
    if (node->Right != NULL) printTreePostOrder(node->Right);
    cout << node->key << " ";
}

static void printTreeInOrder(BSTNode* node) // task 1c
{
    if (node->Left != NULL)printTreeInOrder(node->Left);
    cout << node->key << " ";
    if (node->Right != NULL) printTreeInOrder(node->Right);
}

static BSTNode* min(BSTNode* root) //task 2a
{
    while (root->Left != NULL) root = root->Left;
    return root;
}

static BSTNode* max(BSTNode* root) //task 2b
{
    while (root->Right != NULL) root = root->Right;
    return root;
}

int height(BSTNode* root)
{
    if (root == NULL) return 0;
    else
    {
        int left_height = height(root->Left);
        int right_height = height(root->Right);

        if (left_height >= right_height) return left_height + 1;
        else return right_height + 1;
    }
}

BSTNode* successor(BSTNode* node)
{
    if (node->Right != NULL) return min(node->Right);
    else
    {
        BSTNode* nodeTmp = node->Parent;
        while (nodeTmp != NULL && nodeTmp->Left != node)
        {
            node = nodeTmp;
            nodeTmp = nodeTmp->Parent;
        }
        return nodeTmp;
    }
}

BSTNode* predecessor(BSTNode* node)
{
    if (node->Left != NULL) return max(node->Left);
    else
    {
        BSTNode* nodeTmp = node->Parent;
        while (nodeTmp != NULL && nodeTmp->Right != node)
        {
            node = nodeTmp;
            nodeTmp = nodeTmp->Parent;
        }
        return nodeTmp;
    }
}

BSTNode* Delete(BSTNode* Tree, BSTNode* DeleteNode) {
    BSTNode* y;
    if (DeleteNode->Left == nullptr || DeleteNode->Right == nullptr)
        y = DeleteNode;
    else
        y = successor(DeleteNode);
    BSTNode* x;
    if (y->Left != nullptr)
        x = y->Left;
    else
        x = y->Right;
    if (x != nullptr)
        x->Parent = y->Parent;
    if (y->Parent == nullptr)
        Tree = x;
    else if (y == y->Parent->Left)
        y->Parent->Left = x;
    else
        y->Parent->Right = x;
    if (y != DeleteNode) {
        DeleteNode->key = y->key;
    }
    return y;
}


int main()
{

    BSTNode* root = NULL;
    BSTNode* min_node = NULL;
    BSTNode* succ_node = NULL;
    root = BSTNode::Insert(root, 15);
    root = BSTNode::Insert(root, 10);
    root = BSTNode::Insert(root, 20);
    root = BSTNode::Insert(root, 25);
    root = BSTNode::Insert(root, 8);
    root = BSTNode::Insert(root, 12);


    cout << "TASK 1:\n";

    cout << "BSTNode, print method - PreOrder: ";
    printTreePreOrder(root);

    cout << "\nBSTNode, print method - PostOrder: ";
    printTreePostOrder(root);

    cout << "\nBSTNode, print method - InOrder: ";
    printTreeInOrder(root);


    cout << "\n\n\nTASK 2:\n";

    cout << "Minimum BSTNode vlue: " << min(root)->key;

    cout << "\nMaximum BSTNode vlue: " << max(root)->key;


    cout << "\n\n\nTASK 3:\n";

    cout << "BSTNode height: " << height(root);


    cout << "\n\n\nTASK 4:\n";

    cout << "root's successor: " << successor(root)->key;

    cout << "\nroot's perdecessor: " << predecessor(root)->key;


    cout << "\n\n\nTASK 5:\n";

    cout << "BSTNode before action (in-order method): ";
    printTreeInOrder(root);

    Delete(root, root);

    cout << "\nBSTNode after action (in-order method): ";
    printTreeInOrder(root);

    return 0;
}