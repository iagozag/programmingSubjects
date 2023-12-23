#ifndef AVL_TREE_H
#define AVL_TREE_H

struct node {
    int data;
    node* left;
    node* right;
    int height;
};

class AVLTree {
    private:
        node* root;
    
        void makeEmpty(node* t);
    
        int height(node* t);
    
        int max(int a, int b);
    
        node* rightRotate(node* t);
    
        node* leftRotate(node* t);
    
        int getBalanceFactor(node* N);
    
        node* insert(int x, node* t);
    
        node* remove(int x, node* t);
    
        node* min_node(node* t);
    
        void preorder(node* t);
    
        void inorder(node* t);
    
        void posorder(node* t);
    
    public:
        AVLTree();

        ~AVLTree(); 

        void insert(int x);
    
        void remove(int x);
    
        void display();
};

#endif
