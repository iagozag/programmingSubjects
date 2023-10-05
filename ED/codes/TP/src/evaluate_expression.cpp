#include "../include/Evaluate_expression.h"
#include "../include/Stack.h"

using namespace std;

int priority(const char& c){
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

string infix_to_postfix(string& st, string values){
    Stack<char> s;
    string result = "";
    int N = st.size();

    for(int i = 0; i < N; i++){
        char c = st[i];

        if(st[i] == ' ') continue;

        if((c >= '0' && c <= '9'))
            result += values[c-'0'];

        else if(c == '(') 
            s.push(c);

        else if(c == ')'){
            while(!s.empty() && s.top() != '(')
                result += s.pop();
            if(!s.empty()) s.pop();
        }

        else{
            while(!s.empty() && priority(c) <= priority(s.top()))
                result += s.pop();
            s.push(c);
        }
    }

    while(!s.empty())
        result += s.pop();

    return result;
}

bool evaluate(string& st, string values){
    if(values == "0") return 0;

    for(auto& x: values) if(x == 'a') x = '1';

    string postfix = infix_to_postfix(st, values);

    Stack<int> s;
    int v1, v2, N = postfix.size();
    for(int i = 0; i < N; i++){
        char c = postfix[i];

        if(c == '0' || c == '1')
            s.push(c-'0');

        else if(c == '~')
            s.push(!s.pop());

        else if(c == '&'){
            v1 = s.pop(), v2 = s.pop();
            s.push(v1 && v2);
        }

        else{
            v1 = s.pop(), v2 = s.pop();
            s.push(v1 || v2);
        }
    }

    return s.pop();
}
