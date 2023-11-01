#include "../include/linked_list.h"
#include "../include/memlog.h"

NodeType::NodeType(){
    data = -1;
    next = nullptr;
}

int LinkedList::id_ = 1;

LinkedList::LinkedList(){
    head = new NodeType();
    last = head;
    length = 0;
    escreveMemLog((long int)(head),sizeof(double),id_);
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

    escreveMemLog((long int)(newNode),sizeof(double),id_);
}

NodeType* LinkedList::at(int pos){
    if ((pos >= length) || (pos < 0))
        throw "ERRO: Posicao Invalida!";

    NodeType* p = head->next;
    for(int i=0; i<pos; i++)
        p = p->next;

    leMemLog((long int)(p),sizeof(double),id_);

    return p;
}

int LinkedList::getItem(int pos){
    NodeType* p = at(pos);
    leMemLog((long int)(p),sizeof(double),id_);
    return p->data;
}

void LinkedList::clear() {
    NodeType* p = head->next;
    while(p != NULL) {
        head->next = p->next;
        leMemLog((long int)(p),sizeof(double),id_);
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
