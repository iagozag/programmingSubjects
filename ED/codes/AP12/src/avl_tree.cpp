#include <iostream>

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

using namespace std;

class AVLTree {
private:
    struct node {
        int data;
        node* left;
        node* right;
        int height;
    };

    node* root;

    void makeEmpty(node* t) {
        if (t == nullptr) return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    int height(node* t) {
        return (t == nullptr ? -1 : t->height);
    }

    int updateHeight(node* t) {
        t->height = max(height(t->left), height(t->right)) + 1;
        return t->height;
    }

    int max(int a, int b) {
        return (a > b ? a : b);
    }

    node* rightRotate(node* t) {
        if (t == nullptr || t->left == nullptr) return t;

        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    node* leftRotate(node* t) {
        if (t == nullptr || t->right == nullptr) return t;

        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    node* insert(int x, node* t) {
        if (t == nullptr) {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = nullptr;
        }
        else if (x < t->data)
            t->left = insert(x, t->left);
        else if (x > t->data)
            t->right = insert(x, t->right);
        else
            return t;

        t->height = updateHeight(t);

        int balanceFactor = height(t->left) - height(t->right);

        if (balanceFactor > 1) {
            if (x < t->left->data)
                return rightRotate(t);
            else {
                t->left = leftRotate(t->left);
                return rightRotate(t);
            }
        }
        else if (balanceFactor < -1) {
            if (x > t->right->data) {
                t->right = rightRotate(t->right);
                return leftRotate(t);
            }
            else
                return leftRotate(t);
        }

        return t;
    }

    node* remove(int x, node* t) {
        if (t == nullptr) return nullptr;

        if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else {
            if (t->left == nullptr && t->right == nullptr) {
                delete t;
                return nullptr;
            }
            else if (t->left == nullptr && t->right != nullptr) {
                node* subRightTree = t->right;
                delete t;
                return subRightTree;
            }
            else if (t->left != nullptr && t->right == nullptr) {
                node* subLeftTree = t->left;
                delete t;
                return subLeftTree;
            }
            else {
                node* maxLeftNode = max_node(t->left);
                t->data = maxLeftNode->data;
                t->left = remove(maxLeftNode->data, t->left);
            }
        }

        t->height = updateHeight(t);

        int balanceFactor = height(t->left) - height(t->right);

        if (balanceFactor > 1) {
            if (height(t->left->left) >= height(t->left->right))
                return rightRotate(t);
            else {
                t->left = leftRotate(t->left);
                return rightRotate(t);
            }
        }
        else if (balanceFactor < -1) {
            if (height(t->right->left) > height(t->right->right)) {
                t->right = rightRotate(t->right);
                return leftRotate(t);
            }
            else
                return leftRotate(t);
        }

        return t;
    }

    node* max_node(node* t) {
        if (t->right == nullptr) return t;
        else return max_node(t->right);
    }

    void preorder(node* t) {
        if (t == nullptr) return;

        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }

    void inorder(node* t) {
        if (t == nullptr) return;

        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void posorder(node* t) {
        if (t == nullptr) return;

        posorder(t->left);
        posorder(t->right);
        cout << t->data << " ";
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        preorder(root);
        cout << endl;

        inorder(root);
        cout << endl;

        posorder(root);
        cout << endl;
    }

    ~AVLTree() {
        makeEmpty(root);
    }
};

int main(){ _
    AVLTree tree;
    int n; cin >> n;
    while(n--){
        char op; int data; cin >> op >> data;

        if(op == 'i') tree.insert(data);
        else if(op == 'r') tree.remove(data);
    }

    tree.display();

    return(0);
}
