#include "../include/functions.h"

int main(){
    FACT qs = FACT();
    mc n;

    for(int i = 0; i < 2; i++){
        cin >> n;
        cout << "Fatorando " << n << ":" << endl;

        if (num_length(n, 2) > 80){
            cout << "AVISO: fatorar numeros com mais de 80 bits pode levar muito tempo ou até travar devido ao uso excessivo de memoria" << endl;
        }

        mc f1, f2;
        bool ok = qs.quadSieve(n, f1, f2);

        if(!ok){
            cout << "Fatoracao falhou!" << endl;
            continue;
        }

        if (f1 == 1 and f2 == n){
            cout << n << " eh primo" << endl;
            continue;
        } else{
            mc res = f1*f2;
            assert(res == n);
        }

        cout << "mdc(x - y, N) = " << f1 << endl;
        cout << "mdc(x + y, N) = " << f2 << endl;

        cout << endl;
    }

    exit(0);
}
