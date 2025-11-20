#include "tree_traversal.h"
#include <iostream>
#include <queue>

using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree() : root(nullptr) {}

TreeNode* BinaryTree::insertRecursive(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }
    
    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }
    
    return node;
}

void BinaryTree::insert(int value) {
    root = insertRecursive(root, value);
}

void BinaryTree::inOrderRecursive(TreeNode* node) const {
    if (node != nullptr) {
        inOrderRecursive(node->left);
        cout << node->value << " ";
        inOrderRecursive(node->right);
    }
}

void BinaryTree::preOrderRecursive(TreeNode* node) const {
    if (node != nullptr) {
        cout << node->value << " ";
        preOrderRecursive(node->left);
        preOrderRecursive(node->right);
    }
}

void BinaryTree::postOrderRecursive(TreeNode* node) const {
    if (node != nullptr) {
        postOrderRecursive(node->left);
        postOrderRecursive(node->right);
        cout << node->value << " ";
    }
}

int BinaryTree::getHeightRecursive(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);
    return max(leftHeight, rightHeight) + 1;
}

void BinaryTree::inOrderTraversal() const {
    cout << "Центрированный обход: ";
    inOrderRecursive(root);
    cout << endl;
}

void BinaryTree::preOrderTraversal() const {
    cout << "Прямой обход: ";
    preOrderRecursive(root);
    cout << endl;
}

void BinaryTree::postOrderTraversal() const {
    cout << "Обратный обход: ";
    postOrderRecursive(root);
    cout << endl;
}

int BinaryTree::getHeight() const {
    return getHeightRecursive(root);
}

void BinaryTree::clearTree(TreeNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

BinaryTree::~BinaryTree() {
    clearTree(root);
}

void interactiveTreeTraversal() {
    cout << "\n=== ЗАДАНИЕ 5: ДВОИЧНОЕ ДЕРЕВО ===" << endl;
    cout << "Введите числа для построения дерева (0 для завершения):" << endl;
    
    BinaryTree tree;
    int value;
    
    while (true) {
        cout << "Введите число: ";
        cin >> value;
        if (value == 0) break;
        tree.insert(value);
    }
    
    cout << "\nРезультаты:" << endl;
    tree.inOrderTraversal();
    tree.preOrderTraversal();
    tree.postOrderTraversal();
    cout << "Высота дерева: " << tree.getHeight() << endl;
}
