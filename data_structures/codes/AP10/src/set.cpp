#include "../include/Set.hpp"

StringSet::StringSet(int tamanho){
    tamanhoOriginal = tamanho,
    tamanhoTabela = tamanho,
    tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanho];
}

StringSet::~StringSet(){
    delete[] tabela;
}

int StringSet::Hash(string s){
    int sum = 0;
    for(auto& x: s) sum += x;
    return sum % tamanhoTabela;
}

void StringSet::Rehash(int pos){

}

void StringSet::Resize(size_t tamanho){
    ElementoTabela* novaTabela = new ElementoTabela[tamanho];
    tamanhoTabela = tamanho;

    for(int i = 0; i < tamanhoOriginal; i++){
        if(!tabela[i].vazio){
            int pos = Hash(tabela[i].dado);
            while(!novaTabela[pos].vazio)
                pos = (pos+1) % tamanhoTabela;

            novaTabela[pos] = tabela[i];
        }
    }

    delete[] tabela;
    tabela = novaTabela;
    tamanhoOriginal = tamanho;
}

void StringSet::Inserir(string s){
    if(Pertence(s)) return;

    if((tamanhoConjunto)*2 > tamanhoTabela) 
        Resize(tamanhoTabela*2);

    int pos = Hash(s);
    while(!tabela[pos].vazio)
        pos = (pos+1) % tamanhoTabela;

    tabela[pos].dado = s;
    tabela[pos].vazio = false;
    tabela[pos].retirada = false;
    tamanhoConjunto++;
}

void StringSet::Remover(string s){
    int pos = Hash(s);

    while(!tabela[pos].vazio){
        if(tabela[pos].dado == s)
            tabela[pos].vazio = true,
            tabela->retirada = true,
            tamanhoConjunto--;

        pos = (pos+1) % tamanhoTabela;
    }
}

bool StringSet::Pertence(string s){
    int pos = Hash(s), prev = pos;
    while(!tabela[pos].vazio){
        if(tabela[pos].dado == s && !tabela[pos].retirada)
            return true;

        pos = (pos + 1) % tamanhoTabela;
        if(pos == prev) break;
    }

    return false;
}
        
StringSet* StringSet::Intersecao(StringSet* S){
    StringSet* ans = new StringSet(tamanhoTabela);

    for(int i = 0; i < tamanhoTabela; i++)
        if(!tabela[i].vazio & S->Pertence(tabela[i].dado))
            ans->Inserir(tabela[i].dado);

    return ans;
}

StringSet* StringSet::Uniao(StringSet* S){
    StringSet* ans = new StringSet(tamanhoTabela);

    for(int i = 0; i < tamanhoTabela; i++)
        if(!tabela[i].vazio) 
            ans->Inserir(tabela[i].dado);

    for(int i = 0; i < S->tamanhoTabela; i++)
        if(!S->tabela[i].vazio) 
            ans->Inserir(S->tabela[i].dado);

    return ans;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S){
    StringSet* ans = new StringSet(tamanhoTabela);

    for(int i = 0; i < tamanhoTabela; i++)
        if(!tabela[i].vazio & !S->Pertence(tabela[i].dado))
            ans->Inserir(tabela[i].dado);

    for(int i = 0; i < S->tamanhoTabela; i++)
        if(!S->tabela[i].vazio & !Pertence(S->tabela[i].dado))
            ans->Inserir(S->tabela[i].dado);

    return ans;
}

void StringSet::Imprimir(){
    int cnt = 0;
    cout << "{ ";
    for (int i = 0; i < tamanhoTabela; i++){
        if(!tabela[i].vazio){
            cout << tabela[i].dado << ((cnt+1 == tamanhoConjunto) ? " " : ", ");
            cnt++;
        }
    }
    cout << "}" << endl;
}
