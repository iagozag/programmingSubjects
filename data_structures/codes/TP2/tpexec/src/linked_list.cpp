#include "../include/linked_list.h"

NodeType::NodeType(){
    data = -1;
    next = nullptr;
}

int NodeType::getData(){
    return data;
}

NodeType* NodeType::getNext(){
    return next;
}

LinkedList::LinkedList(){
    head = new NodeType();
    last = head;
    length = 0;
}

LinkedList::~LinkedList() {
    clear();
    delete head;
}

int LinkedList::getLength() {
    return length;
}

bool LinkedList::empty() {
    return length == 0;
}

void LinkedList::insert(const int& item) {
    NodeType* newNode = new NodeType();
    newNode->data = item;

    last->next = newNode;
    last = newNode;
    length++;
}

NodeType* LinkedList::getFirst(){
    return head->next;
}   

void LinkedList::clear() {
    NodeType* p = head->next;
    while(p != NULL) {
        head->next = p->next;
        delete p;
        p = head->next;
    }

    last = head;
    length = 0;
}

AdjacencyList::AdjacencyList(int n){
    length = n;
    list = new LinkedList[length];
}

AdjacencyList::~AdjacencyList(){
    delete[] list;
}

int AdjacencyList::getLen(){
    return length;
}

NodeType* AdjacencyList::getFirst(int x){
    return list[x].getFirst();
}

void AdjacencyList::addEdge(int v, int w){
    list[v].insert(w);
}

int AdjacencyList::degree(int x){
    return list[x].getLength();
}
