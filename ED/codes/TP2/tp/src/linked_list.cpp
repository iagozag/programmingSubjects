#include "../include/linked_list.h"
#include "../include/memlog.h"

NodeType::NodeType(){
    data = -1;
    next = nullptr;
}

int NodeType::getData(){
    leMemLog((long int)(data),sizeof(NodeType),1);
    return data;
}

NodeType* NodeType::getNext(){
    leMemLog((long int)(next),sizeof(NodeType),1);
    return next;
}

int LinkedList::id_ = 2;

LinkedList::LinkedList(){
    head = new NodeType();
    last = head;
    length = 0;
    id_++;
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

    escreveMemLog((long int)(newNode),sizeof(NodeType),id_);
}

NodeType* LinkedList::getFirst(){
    return head->next;
}   

void LinkedList::clear() {
    NodeType* p = head->next;
    while(p != NULL) {
        leMemLog((long int)(p),sizeof(NodeType),id_);
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
