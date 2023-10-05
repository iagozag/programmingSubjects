//---------------------------------------------------------------------
// Arquivo      : vetop.c
// Conteudo     : programa de avaliacao do TAD VET 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2022-04-01 - arquivo criado
//---------------------------------------------------------------------

#include <iomanip>
#include <iostream>
#include <string.h>
#include <sys/resource.h>
#include "../include/fat.h"
#include "../include/fib.h"
#include "../include/msgassert.h"

using namespace std;

#define FATITERATIVO "fati"
#define FATRECURSIVO "fatr"
#define FIBITERATIVO "fibi"
#define FIBRECURSIVO "fibr"

#define BILLION  1000000000L;

float diffUserTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) +
           1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

float diffSystemTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
           1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}

int main(int argc, char ** argv){
    string op = argv[1];
    int n = stoi(argv[2]);
    long long times = stoi(argv[3]), ans = 0;

    struct timespec start, stop;
    struct rusage start_, stop_;
    double clock_time;

    if(clock_gettime(CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }

    getrusage(RUSAGE_SELF, &start_);

    if(op == FATITERATIVO){
        ans = retornaFatorialIterativo(n);
        for(int i = 0; i < times; i++) retornaFatorialIterativo(n);
    }
    else if(op == FATRECURSIVO){
        ans = retornaFatorialRecursivo(n);
        for(int i = 0; i < times; i++) retornaFatorialRecursivo(n);
    }
    else if(op == FIBITERATIVO){
        ans = retornaFibonacciIterativo(n);
        for(int i = 0; i < times; i++) retornaFibonacciIterativo(n);
    }
    else if(op == FIBRECURSIVO){
        ans = retornaFibonacciRecursivo(n);
        for(int i = 0; i < times; i++) retornaFibonacciRecursivo(n);
    }
    else cout << "Comando invalido!" << endl;
       
    getrusage(RUSAGE_SELF, &stop_);

    if(clock_gettime(CLOCK_REALTIME, &stop) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    
    clock_time = ( stop.tv_sec - start.tv_sec )
          + (double) ( stop.tv_nsec - start.tv_nsec )
          / (double) BILLION;

    cout << "Answer: " << ans << endl;
    cout << "Clock time: " << fixed << clock_time << setprecision(6) << endl;
    cout << "CPU time: " << fixed << diffUserTime(&start_, &stop_) << setprecision(6) << " sec user, "
         << fixed << diffSystemTime(&start_, &stop_) << setprecision(6) << " sec system" << endl;

	exit(0);
}
