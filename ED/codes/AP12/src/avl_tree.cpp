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
        return (t == nullptr ? 0 : t->height);
    }

    int max(int a, int b) {
        return (a > b ? a : b);
    }

    node* rightRotate(node* t) {
        node* u = t->left;
        node* T2 = u->right;
        u->right = t;
        t->left = T2;

        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), height(u->right)) + 1;
        return u;
    }

    node* leftRotate(node* t) { 
        node* u = t->right;
        node* T2 = u->left;
        u->left = t;
        t->right = T2;

        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    int getBalanceFactor(node* N) {
        if (N == NULL) return 0;
        return height(N->left) - height(N->right);
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

        t->height = 1 + max(height(t->left), height(t->right));

        int balanceFactor = getBalanceFactor(t);

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
                return leftRotate(t);
            }
            else{
                t->right = rightRotate(t->right);
                return leftRotate(t);
            }
        }

        return t;
    }

    node* remove(int x, node* t) {
        if (t == nullptr) return t;

        if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else {
            if (t->left == nullptr || t->right == nullptr) {
                node* tmp = t->left ? t->left : t->right;

                if(tmp == nullptr) tmp = t, t = nullptr;
                else *t = *tmp, delete(tmp);
            } else{
                node* tmp = min_node(t->right);
                t->data = tmp->data;
                t->right = remove(tmp->data, t->right);
            }
        }

        if(t == nullptr) return t;

        t->height = 1 + max(height(t->left), height(t->right));

        int balanceFactor = getBalanceFactor(t);
        if (balanceFactor > 1) {
            if (getBalanceFactor(t->left) >= 0)
                return rightRotate(t);
            else {
                t->left = leftRotate(t->left);
                return rightRotate(t);
            }
        } else if (balanceFactor < -1) {
            if (getBalanceFactor(t->right) <= 0)
                return leftRotate(t);
            else{
                t->right = rightRotate(t->right);
                return leftRotate(t);
            }
        }

        return t;
    }

    node* min_node(node* t) {
        node* cur = t;
        while(cur->left != nullptr) cur = cur->left;
        return cur;
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
