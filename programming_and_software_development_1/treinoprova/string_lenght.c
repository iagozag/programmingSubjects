#include <stdio.h>

int str_lenght(char* s, int i){
    if(s[i] == NULL) return i;
    return(str_lenght(s, i + 1));
}

int main(){
    char s[100]; gets(s);

    printf("%s has %d characters\n", s, str_lenght(s, 0));
    return(0);
}
