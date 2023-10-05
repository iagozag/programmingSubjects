#include "../include/Binary_tree.h"
#include "../include/Stack.h"
#include "../include/Evaluate_expression.h"

#include <iostream>

NodeType::NodeType()
{
    item = "";
    esq = NULL;
    dir = NULL;
}

string NodeType::getItem(){
    return item;
}

BinaryTree::BinaryTree(string expression)
{
    expression_ = expression;
    root = NULL;
}

BinaryTree::~BinaryTree(){
    clear();
}

NodeType* BinaryTree::get_root(){
    return root;
}

void BinaryTree::insert(string item){
    InsertRecursive(root,item);
}

void BinaryTree::clear(){
    DeleteRecursive(root);
    root = NULL;
}

string change_letter_by_num(string s, char num){
    bool flag = false;
    for(auto& x: s)
        if(x == 'a' || x == 'e'){
            x = num, flag = true;
            break;
        }

    if(flag) return s;
    return "-1";
}

void BinaryTree::InsertRecursive(NodeType* &p, string item){
    p = new NodeType();
    p->item = item;

    if(change_letter_by_num(item, '0') != "-1"){
        InsertRecursive(p->esq, change_letter_by_num(item, '0'));
        InsertRecursive(p->dir, change_letter_by_num(item, '1'));
    }
}

void BinaryTree::DeleteRecursive(NodeType* p){
    if(p!=NULL){
        DeleteRecursive(p->esq);
        DeleteRecursive(p->dir);
        delete p;
    }
}

bool BinaryTree::posOrder(NodeType *p){
    if(p!=NULL){
        posOrder(p->esq);
        posOrder(p->dir);

        char letter;
        for(unsigned i = 0; i < p->item.size(); i++) if(p->item[i] == 'a' || p->item[i] == 'e'){
            letter = p->item[i];
            break;
        }

        if(p->esq != NULL){ 
            bool e1 = evaluate(expression_, p->esq->item), e2 = evaluate(expression_, p->dir->item);

            if(letter == 'a' && !(e1 && e2)){
                p->item = "0";
                return 0;
            }

            else if(letter == 'e'){
                if(!(e1 || e2)) return 0;

                else if(e1 && e2){
                    for(unsigned i = 0; i < p->item.size(); i++) if(p->esq->item[i] != p->dir->item[i]){
                        if(p->esq->item[i] == 'a') p->item[i] = p->dir->item[i];
                        else if(p->dir->item[i] == 'a') p->item[i] = p->dir->item[i];
                        else p->item[i] = 'a';
                    }
                }

                else if(e1) p->item = p->esq->item;

                else p->item = p->dir->item;
            }
        }
    }

    return 1;
}
