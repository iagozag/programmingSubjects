#include "../include/linked_list.h"

NodeType::NodeType(){
    data = -1;
    next = nullptr;
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

NodeType* LinkedList::at(int pos){
    if ((pos >= length) || (pos < 0))
        throw "ERRO: Posicao Invalida!";

    NodeType* p = head->next;
    for(int i=0; i<pos; i++)
        p = p->next;

    return p;
}

int LinkedList::getItem(int pos){
    NodeType* p = at(pos);
    return p->data;
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

void AdjacencyList::addEdge(int v, int w){
    list[v].insert(w);
}

int AdjacencyList::degree(int x){
    return list[x].getLength();
}

int AdjacencyList::getEdges(int x, int y){
    return list[x].getItem(y);
}
