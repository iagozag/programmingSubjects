#include "../include/Stack.h"
#include "../include/Binary_tree.h"

template <class T>
Stack<T>::Stack(){
    length = 0;
}

template <class T>
bool Stack<T>::empty(){
    return (length == 0);
}

template <class T>
void Stack<T>::push(T item){
    if(length == MAXLEN)
        throw stack_overflow_e();

    length++;
    itens[length-1] = item;
}

template <class T>
T Stack<T>::top(){
    return itens[length-1];
}

template <class T>
T Stack<T>::pop(){
    if(empty())
        throw empty_stack_e();

    T aux = itens[length-1];
    length--;

    return aux;
}

template <class T>
void Stack<T>::clear(){
    length = 0;
}

template class Stack<char>;
template class Stack<int>;
