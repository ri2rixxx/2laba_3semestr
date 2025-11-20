#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val);
};

struct BinaryTree {
    TreeNode* root;
    
    BinaryTree();
    void insert(int value);
    void inOrderTraversal() const;
    void preOrderTraversal() const;
    void postOrderTraversal() const;
    int getHeight() const;
    ~BinaryTree();
    
private:
    TreeNode* insertRecursive(TreeNode* node, int value);
    void inOrderRecursive(TreeNode* node) const;
    void preOrderRecursive(TreeNode* node) const;
    void postOrderRecursive(TreeNode* node) const;
    int getHeightRecursive(TreeNode* node) const;
    void clearTree(TreeNode* node);
};

void interactiveTreeTraversal();

#endif
