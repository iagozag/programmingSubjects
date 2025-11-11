#include <iostream>
#include <string.h>
#include <getopt.h>

#include "../include/Stack.h"
#include "../include/Evaluate_expression.h"
#include "../include/Binary_tree.h"
#include "../include/memlog.h"

using namespace std;

#define EVALUATEEXPRESSION 'a'
#define SATISFIABILITY 's'

typedef struct opt{
  int opescolhida;
  char lognome[100];
  int regmem;
  string expression, values;
} opt_tipo;

void parse_args(int argc,char** argv, opt_tipo * opt){
    static struct option long_options[] = {
        {"a", required_argument, 0, 'a'},
        {"s", required_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    int c;

    opt->opescolhida = -1;
    opt->regmem = 0;
    opt->lognome[0] = 0;
    opt->expression = "";
    opt->values = "";

    while ((c = getopt_long(argc, argv, "a:s:p:l", long_options, NULL)) != EOF){
        switch(c) {
            case 'a':
	            opt->opescolhida = EVALUATEEXPRESSION;
                opt->expression = optarg; 
                opt->values = argv[optind]; 
                break;
            case 's':
	            opt->opescolhida = SATISFIABILITY;
                opt->expression = optarg; 
                opt->values = argv[optind]; 
                break;
            case 'p': 
	            strcpy(opt->lognome,optarg);
		        break;
            case 'l': 
	            opt->regmem = 1;
		        break;
            default:
                exit(1);
        }
    }
}

string acessaString(string st){
    size_t i;
    string s;
    char aux;
    for (i=0; i<st.size(); i++){
        aux = st[i];
        s+=aux;
        leMemLog((long int)(&(st[i])),sizeof(string),1);
    }
    return s;
}

int main(int argc, char** argv){
    opt_tipo opt;
    parse_args(argc, argv, &opt);

    iniciaMemLog(opt.lognome);

    // ativar ou nao o registro de acesso
    if (opt.regmem){ 
      ativaMemLog();
    }
    else{
      desativaMemLog();
    }

    if(opt.opescolhida == EVALUATEEXPRESSION){
        try{
            defineFaseMemLog(0);
            acessaString(opt.expression);
            acessaString(opt.values);
            defineFaseMemLog(1);
            cout << evaluate(opt.expression, opt.values) << endl;
            defineFaseMemLog(2);
        } catch(stack_overflow_e e){
            cout << "A pilha está cheia!" << endl;
        } catch(empty_stack_e e){
            cout << "A pilha está vazia!" << endl;
        }
    }
    else if(opt.opescolhida == SATISFIABILITY){
        try{
            defineFaseMemLog(0);
            acessaString(opt.expression);
            acessaString(opt.values);
            BinaryTree bt(opt.expression, 2);
            bt.insert(opt.values);
            bt.posOrderA(bt.get_root());
            defineFaseMemLog(1);
            (bt.posOrder(bt.get_root())) ? cout << 1 << " " << bt.get_root()->getItem() << endl :
                                           cout << 0 << endl;
            defineFaseMemLog(2);
            bt.posOrderA(bt.get_root());
            bt.clear();
        } catch(stack_overflow_e e){
            cout << "A pilha está cheia!" << endl;
        } catch(empty_stack_e e){
            cout << "A pilha está vazia!" << endl;
        }
    }
    else cout << "Comando invalido!" << endl;

    return finalizaMemLog();
}

