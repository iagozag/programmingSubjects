#include <stdio.h>

float media_matriz(int n, float mat[][100]){
	int soma = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			soma += mat[i][j];
		}
	}
	return(soma / (n * n));
}

void identidade(int n, float A[][100]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) A[i][j] = 1;
			else A[i][j] = 0;
		}
	}
}

void transposta(int n, float A[][100], float T[][100]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			T[i][j] = A[j][i];
		}
	}
}

int simetrica(int n, float A[][100]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(A[i][j] != A[j][i]) return 0;
		}
	}
	return 1;
}

void soma_matriz(int n, float A[][100], float B[][100], float S[][100]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			S[i][j] = A[i][j] + B[i][j];
		}
	}
}

void mult_matriz(int n, float A[][100], float B[][100], float P[][100]){
    int aux;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
            aux = 0;
            for(int k = 0; k < n; k++){
                aux += A[i][k] * B[k][j];
            }
            P[i][j] = aux;
		}
	}
}

int main(){
	FILE *f1 = fopen("dados.txt", "r+t");

	if(f1 == NULL){
		printf("ERRO AO ABRIR ARQUIVO!");
		return(1);
	}

	int linhas, colunas;
	float mat[100][100];
	float A[100][100] = {
		{0, 5, 4},
		{2, 9, 10},
		{6, 5, 2}
	};
	float T[100][100];
	float S[100][100];
	float P[100][100];

	fscanf(f1, "%d %d", &linhas, &colunas);
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			fscanf(f1, "%f", &mat[i][j]);
		}
	}

	printf("mat:\n");
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.0f ", mat[i][j]);
		}
		printf("\n");
	}

	printf("media: %f\n", media_matriz(linhas, mat));
	identidade(3, A);

	printf("\nA:\n");
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.0f ", A[i][j]);
		}
		printf("\n");
	}

	transposta(3, mat, T);
	printf("\nT:\n");
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.0f ", T[i][j]);
		}
		printf("\n");
	}

	printf("\nA matriz eh simetrica? %d\n", simetrica(3, A));

	soma_matriz(3, mat, A, S);
	printf("\nsoma:\n");
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.0f ", S[i][j]);
		}
		printf("\n");
	}

	mult_matriz(3, mat, T, P);
	printf("\nproduto:\n");
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%.0f ", P[i][j]);
		}
		printf("\n");
	}

	fclose(f1);
	return 0;
}
