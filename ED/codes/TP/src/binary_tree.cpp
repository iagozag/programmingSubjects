#include "../include/Binary_tree.h"
#include "../include/Stack.h"
#include "../include/Evaluate_expression.h"

#include <iostream>
using namespace std;

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

        if(p->esq != NULL){        
            char letter;
            for(size_t i = 0; i < p->item.size(); ++i) if(p->item[i] == 'a' || p->item[i] == 'e'){
                letter = p->item[i];
                break;
            }

            bool e1 = evaluate(expression_, p->esq->item), e2 = evaluate(expression_, p->dir->item);

            if(letter == 'a'){
                if(!(e1 && e2)){
                    p->item = "-1";
                    return 0;
                }
                
                p->item = resume_string(p->esq->item, p->dir->item);
            }

            else if(letter == 'e'){
                if(!(e1 || e2)){
                    p->item = "-1";
                    return 0;
                }

                else if(e1 && e2) p->item = resume_string(p->esq->item, p->dir->item);

                else if(e1) p->item = p->esq->item;

                else p->item = p->dir->item;
            }
        }
    }

    return 1;
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

string resume_string(string s1, string s2){
    string result = "";
    for(size_t i = 0; i < s1.size(); ++i){
        if(s1[i] != s2[i]){
            if(s1[i] == 'a') result += s2[i];
            else if(s2[i] == 'a') result += s1[i];
            else result += 'a';
        }
        else result += s1[i];
    }

    return result;
}

