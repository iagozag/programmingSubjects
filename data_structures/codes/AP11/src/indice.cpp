#include <iostream>

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

using namespace std;

class AVLTree{
    private:
        struct node
        {
            string data;
            int page;
            node* left;
            node* right;
            int height;
        };

        node* root;
        int cnt = 0, inputs = 0;

        void makeEmpty(node* t)
        {
            if(t == nullptr) return;

            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }

        node* insert(string x, int page, node* t)
        {
            if(t == nullptr){
                t = new node;
                t->data = x;
                t->page = page;
                t->height = 0;
                t->left = t->right = nullptr;
            }

            if(x < t->data || (x == t->data && page < t->page))
                t->left = insert(x, page, t->left);

            else if(x > t->data || (x == t->data && page > t->page))
				t->right = insert(x, page, t->right);

            else if((x == t->data && page == t->page))
				return t;

			int height_L = height(t->left);
			int height_R = height(t->right);

			t->height = max(height_L, height_R);
			
			int balance_factor = height_L - height_R;

			if(balance_factor > 1){
				if(x < t->left->data)
				    return t = rightRotate(t);
				else{
				    t->left = leftRotate(t->left);
				    return t = rightRotate(t);
				}
			}
			else if(balance_factor < -1){
				if(x < t->right->data){
				    t->right = rightRotate(t->right);
				    return t = leftRotate(t);
				}
				else
				    return t = leftRotate(t);
			}

			return t;
	    }

	    node* rightRotate(node* &t){
			if (t == nullptr || t->left == nullptr)
				return t;

			node* u = t->left;
			t->left = u->right;
			u->right = t;
			t->height = max(height(t->left), height(t->right));
			u->height = max(height(u->left), t->height);
			return u;
	    }

	    node* leftRotate(node* &t){
			if (t == nullptr || t->right == nullptr)
				return t;

			node* u = t->right;
			t->right = u->left;
			u->left = t;
			t->height = max(height(t->left), height(t->right));
			u->height = max(height(t->right), t->height);
			return u;
	    }

	    int height(node* t){
			return (t == nullptr ? 0 : t->height+1);
	    }

	    void inorder(node* t, string& prev){
			if(t == nullptr) return;

			inorder(t->left, prev);

			if(t->data != prev)
				cout << (cnt == 0 ? "" : "\n") << t->data << ": " << t->page, prev = t->data, cnt++;
			else cout << " " << t->page;

			inorder(t->right, prev);
	    }

    public:
        AVLTree(){
            root = nullptr;
        }

        void increaseInputs(){
            inputs++;
        }

        void insert(string x, int page){
            root = insert(x, page, root);
        }

        void display(){
            string prev = "";
            inorder(root, prev);
            cout << endl;
        }

        ~AVLTree(){
            makeEmpty(root);
        }
};

int main(){ _
    AVLTree tree;
    string word; int p;
    while(cin >> word >> p)
        tree.insert(word, p), tree.increaseInputs();; 

    tree.display();

    return(0);
}
