#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template<typename> class LinkedList;

template <typename T>
class NodeType {
    T data;
    NodeType* next;

    NodeType(const T& value) : data(value), next(nullptr) {}
    friend class LinkedList<T>;
};


template<typename T>
class LinkedList {
public:
    LinkedList() : length(0), head(nullptr), last(nullptr) {}
    ~LinkedList();

    int getLength();
    bool empty();
    void insert(const T& item);
    T& at(int index);
    void clear();

    void print() const {
        NodeType<T>* current = head;
        while(current) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }

private:
    int length;
    NodeType<T>* head;
    NodeType<T>* last;
};

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
int LinkedList<T>::getLength() {
    return length;
}

template<typename T>
bool LinkedList<T>::empty() {
    return length == 0;
}

template <typename T>
void LinkedList<T>::insert(const T& item) {
    NodeType<T>* newNode = new NodeType<T>(item);

    if (!head) head = newNode;
    else last->next = newNode;

    last = newNode;
    length++;
}

template <typename T>
T& LinkedList<T>::at(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    NodeType<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

template<typename T>
void LinkedList<T>::clear() {
    while(head) {
        NodeType<T>* temp = head;
        head = head->next;
        delete temp;
    }

    last = nullptr;
    length = 0;
}

#endif

