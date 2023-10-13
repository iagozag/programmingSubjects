#include <iostream>
#include <string.h>
#include <getopt.h>

#include "../include/Stack.h"
#include "../include/Evaluate_expression.h"
#include "../include/Binary_tree.h"

using namespace std;

#define EVALUATEEXPRESSION 'a'
#define SATISFIABILITY 's'

static char opt;
string expression, values;

void parse_args(int argc,char** argv){
    static struct option long_options[] = {
        {"a", required_argument, 0, 'a'},
        {"s", required_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    int c;

    opt = -1;
    expression = "";
    values = "";

    while ((c = getopt_long(argc, argv, "a:s:", long_options, NULL)) != EOF){
        switch(c) {
            case 'a':
	            opt = EVALUATEEXPRESSION;
                expression = optarg; 
                values = argv[optind]; 
                break;
            case 's':
	            opt = SATISFIABILITY;
                expression = optarg; 
                values = argv[optind]; 
                break;
            default:
                exit(0);
        }
    }
}

int main(int argc, char** argv){
    parse_args(argc, argv);

    if(opt == EVALUATEEXPRESSION){
        try{
            cout << evaluate(expression, values) << endl;
        } catch(stack_overflow_e e){
            cout << "A pilha está cheia!" << endl;
        } catch(empty_stack_e e){
            cout << "A pilha está vazia!" << endl;
        }
    }
    else if(opt == SATISFIABILITY){
        try{
            BinaryTree bt(expression);
            bt.insert(values); 
            (bt.posOrder(bt.get_root())) ? cout << 1 << " " << bt.get_root()->getItem() << endl :
                                           cout << 0 << endl;
        } catch(stack_overflow_e e){
            cout << "A pilha está cheia!" << endl;
        } catch(empty_stack_e e){
            cout << "A pilha está vazia!" << endl;
        }
    }
    else cout << "Comando invalido!" << endl;

    return(0);
}

