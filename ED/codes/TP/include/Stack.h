#ifndef STACK_H
#define STACK_H

class stack_overflow_e {};
class empty_stack_e {};

template <class T>
class Stack {
    private:
        int length;
        static const int MAXLEN = 1e6;
        T itens[MAXLEN];
    public:
        Stack();

        bool empty();

        void push(T item);

        T top();

        T pop();

        void clear();

        void print();
};

#endif
