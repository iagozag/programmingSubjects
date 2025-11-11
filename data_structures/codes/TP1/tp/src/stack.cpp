#include "../include/Stack.h"
#include "../include/Binary_tree.h"
#include "../include/memlog.h"

template <class T>
Stack<T>::Stack(int id){
    length = 0;
    id_ = id;
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
    escreveMemLog((long int)(&(itens[length-1])),sizeof(double),id_);
}

template <class T>
T Stack<T>::top(){
    leMemLog((long int)(&(itens[length-1])),sizeof(double),id_);
    return itens[length-1];
}

template <class T>
T Stack<T>::pop(){
    if(empty())
        throw empty_stack_e();

    T aux = itens[length-1];
    length--;
    leMemLog((long int)(&(itens[length-1])),sizeof(double),id_);

    return aux;
}

template <class T>
void Stack<T>::clear(){
    length = 0;
}

template class Stack<char>;
template class Stack<int>;
