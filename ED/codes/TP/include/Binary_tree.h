#ifndef TREE_H
#define TREE_H

#include <string>

using namespace std;

class NodeType {
    public:
        NodeType();
        string getItem();
        size_t getSize();

    private:
        string item;
        NodeType *esq;
        NodeType *dir;

    friend class BinaryTree;
};

class BinaryTree {
    public:
        BinaryTree(string expression);
        ~BinaryTree();

        NodeType* get_root();
        void insert(string item);
        void clear();
        bool posOrder(NodeType *p);

    private:
        void InsertRecursive(NodeType* &p, string item);
        void DeleteRecursive(NodeType* p);
        
        string expression_;
        NodeType *root;
};

#endif
