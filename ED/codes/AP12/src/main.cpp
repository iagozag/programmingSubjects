#include <iostream>
using namespace std;

#include "../include/avl_tree.h"

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

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
