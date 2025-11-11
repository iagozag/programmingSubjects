#include<stdio.h>

void imprime_inverso(char s[1000]){
    for(int i = strlen(s) - 1; i >= 0; i--)
        printf("%c", s[i]);
}

void Dec2Bin(int n){
    char str[1000];
    if(n >= 1){
        if(n % 2 == 1){
            str += "1";
            Dec2Bin(n / 2);
        }
        if(n % 2 == 0){
            str += "0";
            Dec2Bin(n / 2);
        }
    }

}

int main(){
    int n; scanf("%d", &n);

    Dec2Bin(n);
    return(0);
}
