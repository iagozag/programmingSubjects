#include "../include/Satisfaction.h"
#include "../include/Binary_tree.h"

#include <iostream>
using namespace std;

Pair::Pair(){
    ans = 0;
    result = "";
}

bool Pair::get_ans(){
    return ans;
}

string Pair::get_res(){
    return result;
}

void Pair::set_ans(bool b){
    ans = b;
}

void Pair::set_result(string res){
    result = res;
}

Pair satisfaction(string& st, string& values){
    Pair answer;

    BinaryTree bt(st);
    bt.insert(values);

    if(bt.posOrder(bt.get_root())){
        answer.set_ans(1);
        answer.set_result(bt.get_root()->getItem());
    }

    return answer;
}
