#include "../include/Evaluate_expression.h"
#include "../include/Stack.h"

#include <iostream>
using namespace std;

int priority(char c){
    switch(c){
        case '~':
            return 3; 
        case '&':
            return 2; 
        case '|':
            return 1;
        default:
            return -1;
    }
}

string infix_to_postfix(string st, string values){
    Stack<char> s(0);
    string result = "";
    int N = st.size();
    for(int i = 0; i < N; i++){
        if(st[i] == ' ') continue;

        if(st[i] >= '0' && st[i] <= '9'){
            string numbuffer = "";
            while(st[i] >= '0' && st[i] <= '9')
                numbuffer += st[i], i++;
            i--;
            result += values[stoi(numbuffer)];
            numbuffer = "";
        }

        else if(st[i] == '(') 
            s.push(st[i]);

        else if(st[i] == ')'){
            while(!s.empty() && s.top() != '(')
                result += s.pop();
            if(!s.empty()) s.pop();
        }

        else{
            while(!s.empty() && priority(st[i]) < priority(s.top()))
                result += s.pop();
            s.push(st[i]);
        }
    }

    while(!s.empty())
        result += s.pop();

    return result;
}

bool evaluate(string st, string values){
    if(values == "-1") return 0;

    for(auto& x: values) if(x == 'a') x = '1';

    string postfix = infix_to_postfix(st, values);

    Stack<int> s(1);
    for(auto& c: postfix){
        if(c == '0' || c == '1')
            s.push(c-'0');

        else if(c == '~')
            s.push(!s.pop());

        else if(c == '&'){
            int v1 = s.pop(), v2 = s.pop();
            s.push(v1 && v2);
        }

        else{
            int v1 = s.pop(), v2 = s.pop();
            s.push(v1 || v2);
        }
    }

    return s.pop();
}

