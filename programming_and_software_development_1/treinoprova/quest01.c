#include <stdio.h>

int main(){
    int n;
    char file[100]; scanf("%s", file);
    FILE *num = fopen(file, "w+t");

    for(int i = 0; i < 5; i++){
        scanf("%d", &n);
        fprintf(num, "%d ", n);
    }
    fclose(num);

    num = fopen(file, "r+t");
    while(fscanf(num, "%d", &n) != EOF){
        printf("%d ", n);
    }
    return(0);
}
