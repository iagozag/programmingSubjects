#include "../include/linked_list.h"

LinkedList::~LinkedList() {
    clear();
}

int LinkedList::getLength() {
    return length;
}

bool LinkedList::empty() {
    return length == 0;
}

void LinkedList::insert(const int& item) {
    NodeType* newNode = new NodeType(item);

    if (!head) head = newNode;
    else last->next = newNode;

    last = newNode;
    length++;
}

NodeType* LinkedList::at(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }

    NodeType* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

NodeType* LinkedList::getNext(NodeType* cur){
    return cur->next;
}

void LinkedList::clear() {
    while(head) {
        NodeType* temp = head;
        head = head->next;
        delete temp;
    }

    last = nullptr;
    length = 0;
}

void LinkedList::print() const {
    NodeType* current = head;
    while(current) {
        std::cout << current->data << " ";
        current = current->next;
    }
}

ListaAdjacencia::ListaAdjacencia(int n){
    tamanho = n;
    lista = new LinkedList[tamanho];
    colors = new int[tamanho];
}

ListaAdjacencia::~ListaAdjacencia(){
    delete[] lista;
    delete[] colors;
}

int ListaAdjacencia::getTam(){
    return tamanho;
}

int ListaAdjacencia::getCor(int x){
    return colors[x];
}

void ListaAdjacencia::adicionaCores(int v[]){
    for(int i = 0; i < tamanho; i++)
        colors[i] = v[i];
}

void ListaAdjacencia::adicionaAresta(int v, int w){
    lista[v].insert(w);
}

LinkedList ListaAdjacencia::getArestas(int x){
    return lista[x];
}

void ListaAdjacencia::imprime(int v){
    lista[v].print();
}
