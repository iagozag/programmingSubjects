#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "passa_tempo.h"

using namespace std;

void inicia_tempo(void);

void passa_tempo(int tid, int gid, int pos, int decimos);

#define MAX_N 20
#define MAX_THREADS 40

// Dados de configuração de cada thread: identificador, grupo, tempo inicial e trajeto
struct ThreadInfo{
    int id, group, start, pos_size;
    vector<pair<int,int>> pos;

    ThreadInfo() {}
    ThreadInfo(int _id,int _group,int _start,int _pos_size, const vector<pair<int,int>>& _pos)
    : id(_id), group(_group), start(_start), pos_size(_pos_size), pos(_pos) {}
};

/*
* Waiter: nó da fila usado para representar uma thread que está bloqueada
* esperando para entrar em alguma posição.
*
* Campos principais:
* - tid, gid: identificador e grupo da thread que está esperando
* - cond: variável de condição do waiter; a thread espera essa condição quando enfileirada
* - paired: sinaliza que a dupla foi formada
* - next: ponteiro para o próximo waiter na fila
*
* Usei uma cond por waiter (em vez de uma cond por posição) para preservar
* a ordem de notificação e acordar apenas as threads que de fato foram
* selecionadas para entrar.
*/
struct Waiter{
    int tid;
    int gid;
    pthread_cond_t cond;
    bool paired;
    Waiter* next;
    Waiter(int _tid,int _gid): tid(_tid), gid(_gid), paired(false), next(NULL){
        pthread_cond_init(&cond, NULL);
    }
    ~Waiter(){
        pthread_cond_destroy(&cond);
    }
};

/*
* Position: representa uma posição no mapa de posições.
*
* - mutex: Faz a mutuação exclusiva da posição
* - head/tail: fila de espera de Waiters
* - qnt: número de threads atualmente ocupando a posição (0, 1 ou 2).
*
* Regras de alto nível:
* - Quando a posição está vazia (qnt == 0), se existir na fila um
* Waiter mais antigo de grupo diferente, ele é pareado com a thread que
* está tentando entrar. Ambos passam a ocupar a posição.
* - Se não houver compatível, a thread que chega se enfileira (cria um Waiter) e
* espera até que alguém compatível apareça.
*/
struct Position{
    pthread_mutex_t mutex;
    Waiter* head;
    Waiter* tail;
    int qnt;

    Position(){
        pthread_mutex_init(&mutex, NULL);
        head = tail = NULL;
        qnt = 0;
    }
};

Position arr[MAX_N];
int N, n_threads;
vector<ThreadInfo> t_info;

/*
* remove_waiter:
* - Remove um nó `node` da fila da posição `pos` sabendo-se o nó anterior `prev`.
* - Deve ser chamado com o mutex da posição já trancado.
*/
static void remove_waiter(Position &pos, Waiter* prev, Waiter* node){
    if(prev) prev->next = node->next;
    else pos.head = node->next;

    if(node == pos.tail) pos.tail = prev;

    node->next = NULL;
}

/*
* entra(id, group, p): rotina que bloqueia até que a thread possa entrar na posição p.
*
* 1) Se a posição estiver vazia (qnt == 0):
* - procura na fila o primeiro waiter mais antigo cujo grupo seja diferente
* do grupo da thread atual. Se encontrar, remove esse waiter
* da fila, marca qnt = 2 e sinaliza o waiter encontrado.
* A thread que chegou entra imediatamente sem esperar.
*
* - se não encontrar nenhum waiter compatível, a thread cria um Waiter
* , anexa na fila e chama pthread_cond_wait sobre sua cond (liberando
* o mutex enquanto espera). Ao retornar de pthread_cond_wait ela verifica
* a flag `paired` em loop antes de prosseguir.
*
* 2) Se a posição estiver ocupada (qnt == 1 ou 2), a thread simplesmente se
* enfileira como waiter e espera até ser pareada por uma chamada a `sai()`.
*/
void entra(int id, int group, int p){
    Position &pos = arr[p-1];
    pthread_mutex_lock(&pos.mutex);

	// Caso posição vazia: tentar parear com o primeiro waiter compatível (chegou antes)
    if(pos.qnt == 0){
        Waiter* prev = NULL;
        Waiter* cur = pos.head;

        while(cur){
            if(cur->gid != group) break; // encontrou compatível
            prev = cur; cur = cur->next;
        }

        if(cur){
			// Encontrou um waiter mais antigo e compatível -> forma dupla
			remove_waiter(pos, prev, cur);

            cur->paired = true;
            pos.qnt = 2;

            pthread_cond_signal(&cur->cond);
            pthread_mutex_unlock(&pos.mutex);
            return;
        }
        else{
			// Não há waiter compatível -> enfileira-se e espera até ser pareada
            Waiter* me = new Waiter(id, group);

            if(pos.tail) pos.tail->next = me; else pos.head = me;
            pos.tail = me;

            while(!me->paired) pthread_cond_wait(&me->cond, &pos.mutex);

            pthread_mutex_unlock(&pos.mutex);
            delete me;
            return;
        }
    }
    else{
		// posição já ocupada (1 ou 2) -> enfileirar e esperar por pareamento futuro
        Waiter* me = new Waiter(id, group);

        if(pos.tail) pos.tail->next = me; else pos.head = me;
        pos.tail = me;

        while(!me->paired) pthread_cond_wait(&me->cond, &pos.mutex);

        pthread_mutex_unlock(&pos.mutex);
        delete me;
        return;
    }
}

/*
* sai(id, p): rotina chamada quando uma thread libera a sua posição p. 
* A função atualiza `qnt` e, se a posição ficar vazia, tenta formar a 
* primeira dupla possível a partir da fila de espera.
*
* Algoritmo resumido:
* - decrementa qnt (com o mutex trancado);
* - se qnt passa a 0, percorre a fila em busca do primeiro par i<j com
* grupos diferentes. Se encontrar, remove ambos da fila, marca-os como
* pareados e sinaliza suas conds. Também define qnt = 2 (dupla entra).
* - se não encontrar par, a posição permanece vazia até que novas threads
* cheguem.
*/
void sai(int id, int p){
    Position &pos = arr[p-1];
    pthread_mutex_lock(&pos.mutex);

    if(pos.qnt > 0) pos.qnt--;

	// Se após a saída a posição ficou vazia, tentar formar uma dupla com a fila
    if(pos.qnt == 0){
        Waiter* prev_i = NULL;
        Waiter* i = pos.head;
        bool formed = false;

        for(; i != NULL && !formed; prev_i = i, i = i->next){
            Waiter* prev_j = i;
            Waiter* j = i->next;

            for(; j != NULL; prev_j = j, j = j->next){
                if(j->gid != i->gid){
					// remove j primeiro (prev_j pode ser i)
                    remove_waiter(pos, prev_j, j);
					// remove i (prev_i pode ser NULL)
                    remove_waiter(pos, prev_i, i);

					// marca ambos como pareados e sinaliza suas conds
                    i->paired = true;
                    j->paired = true;
                    pos.qnt = 2;

                    pthread_cond_signal(&i->cond);
                    pthread_cond_signal(&j->cond);
                    formed = true;
                    break;
                }
            }
        }
    }
	// se não formou par, a posição permanece vazia (qnt == 0)

    pthread_mutex_unlock(&pos.mutex);
}

/*
* Rotina da thread: segue o trajeto, chamando entra/sai conforme o enunciado
* - espera o tempo inicial
* - entra na primeira posição e chama passa_tempo
* - para cada próxima posição: entra(nova), sai(antiga), passa_tempo(nova)
* - ao terminar o trajeto, chama sai da última posição
*
* A ordem entra(), então sai() garante que a thread só libera (sai) a 
* posição anterior depois de garantir que conseguiu entrar na nova posição.
*/
void* routine(void* param){
    ThreadInfo* t = (ThreadInfo*)param;

	// dorme o tempo inicial da thread passado na entrada, conforme feito na função passa tempo
    struct timespec zzz;
    zzz.tv_sec  = t->start/10;
    zzz.tv_nsec = (t->start%10) * 100L * 1000000L;
    nanosleep(&zzz,NULL);

    auto [p, dec] = t->pos[0];

	// Entra na primeira posição na trajetória da thread e passa o tempo necessário
    entra(t->id, t->group, p);
    passa_tempo(t->id, t->group, p, dec);

	/* Segue o algoritmo passado na especificação:
	*   obtém próxima posição P' do trajeto;
    *   quando as regras o permitirem,
    *      entra na próxima posição;
    *      libera a posição anterior;
    *      executa a função passa_tempo com o tempo associado à posição P';
	*/
    for(int i = 1; i < t->pos_size; i++){
		auto [np, ndec] = t->pos[i];

        entra(t->id, t->group, np);
        sai(t->id, p);
        passa_tempo(t->id, t->group, np, ndec);

        p = np;
    }

	// thread sai da última posição da trajetória
    sai(t->id, p);

    return NULL;
}

int main(){ 
	// lê entrada do programa
    cin >> N >> n_threads;

    t_info.resize(n_threads);
    for(int i = 0; i < n_threads; i++){
        int id, group, start, pos_size; cin >> id >> group >> start >> pos_size;

        vector<pair<int,int>> positions;
        for(int j = 0; j < pos_size; j++){
            int pos, dec; cin >> pos >> dec;
            positions.emplace_back(pos, dec);
        }

        t_info[i] = ThreadInfo(id, group, start, pos_size, positions);
    }

	// inicia marcador de tempo
    inicia_tempo();

	// cria threads com a função de rotina de cada uma
    vector<pthread_t> threads(n_threads);
    for(int i = 0; i < n_threads; i++) if(pthread_create(&threads[i], NULL, routine, (void*)&t_info[i])){
		cerr << "ERR: create" << endl; exit(-1); 
	}

    for(int i = 0; i < n_threads; i++) pthread_join(threads[i], NULL);

	// destrói mutex de cada posição do mapa
    for(int i = 0; i < N; i++) pthread_mutex_destroy(&arr[i].mutex);

    return 0;
}
