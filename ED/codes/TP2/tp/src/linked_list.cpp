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

NodeType* LinkedList::Posiciona(int pos){
    if ((pos >= length) || (pos < 0))
        throw "ERRO: Posicao Invalida!";

    NodeType* p = head->next;
    for(int i=0; i<pos; i++)
        p = p->next;

    return p;
}

int LinkedList::getItem(int pos){
    NodeType* p = Posiciona(pos);
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

void LinkedList::print() const {
    NodeType* current = head->next;
    while(current) {
        std::cout << current->data << " ";
        current = current->next;
    }
}

ListaAdjacencia::ListaAdjacencia(int n){
    tamanho = n;
    lista = new LinkedList[tamanho];
}

ListaAdjacencia::~ListaAdjacencia(){
    delete[] lista;
}

int ListaAdjacencia::getTam(){
    return tamanho;
}

void ListaAdjacencia::adicionaAresta(int v, int w){
    lista[v].insert(w);
}

int ListaAdjacencia::degree(int x){
    return lista[x].getLength();
}

int ListaAdjacencia::getArestas(int x, int y){
    return lista[x].getItem(y);
}

void ListaAdjacencia::imprime(int v){
    lista[v].print();
}
