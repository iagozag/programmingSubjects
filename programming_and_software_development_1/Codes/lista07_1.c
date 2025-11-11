#include <stdio.h>

float media(int n, float* v){
	float soma = 0;
	for(int i = 0; i < n; i++){
		soma += v[i];
	}
	return(soma / n);
}

float variancia(int n, float* v){
	float soma = 0;
	float average = media(n, v);
	for(int i = 0; i < n; i++){
		soma += (v[i] - average) * (v[i] - average);
	}
	return(soma / (n - 1));
}

float maximo(int n, float* v){
	float max = v[0];
	for(int i = 0; i < n; i++){
		if(v[i] > max) max = v[i];
	}
	return(max);
}

float minimo(int n, float* v){
	float min = v[0];
	for(int i = 0; i < n; i++){
		if(v[i] < min) min = v[i];
	}
	return(min);
}

float prod_escalar(int n1, int n2, float* v, float* u){
	int soma = 0, tam_max;
	if(n1 > n2) tam_max = n1;
	else tam_max = n2;
	for(int i = 0; i < tam_max; i++){
		soma += v[i] * u[i];
	}
	return(soma);
}

int main(){
	int numeros[1000];
	int i = 0;
	float reais_v[] = {1.0, 2.0, 3.0};
	float reais_u[] = {4.0, 5.0, 7.0};
	int n, tam_v = 3, tam_u = 3;
	FILE* f = fopen("file.txt","r+t");
	
	if(f == NULL) printf("Erro ao abrir arquivo\n");
	else{
		while(fscanf(f, "%d", &n) != EOF){
			numeros[i] = n;
			i++;
		}
	}
	
	for(int j = 0; j < i; j++) printf("%d ", numeros[j]);
	printf("\n%f", media(tam_v, reais_v));
	printf("\n%f", variancia(tam_v, reais_v));
	printf("\n%f", maximo(tam_v, reais_v));
	printf("\n%f", minimo(tam_v, reais_v));
	printf("\n%f", prod_escalar(tam_v, tam_u, reais_v, reais_u));
	
	fclose(f);
	return 0;
}
