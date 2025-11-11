#include <iostream>
#include <math.h>
using namespace std;

float media(float n1, float n2, float n3){
	return (n1 + n2 + n3) / 3;;
}

float media_ponderada(float n1, float n2, float n3){
	return (n1 * 3 + n2 * 4 + n3 * 5) / 12;
}
	
float perimetro_circulo(float raio){
	return 2 * M_PI * raio;
}

float area_circulo(float raio){
	return M_PI * raio * raio;
}

float area_triangulo(float base, float alt){
	return (base * alt) / 2;
}

float area_caixa(float n1, float n2, float n3){
	return n1 * n2 * n3;
}

float volume_caixa(float n1, float n2, float n3){
	return (2 * n1) + (2 * n2) + (2 * n3);
}

float area_cilindro(float raio, float altura){
	return 2 * M_PI * raio * (raio + altura);
}

float volume_cilindro(float raio, float altura){
	return M_PI * raio * raio * altura;
}

float hipotenusa_triangulo(float cat1, float cat2){
	return sqrt((cat1 * cat1) + (cat2 * cat2));
}

float raiz_equacao_2_grau(float a, float b, float c){
	float raiz;
	float delta = (b * b) - (4 * a * c);
	
	if(a != 0){
		if (delta < 0){
			cout << "\nA funcao nao tem raizes reais!";
		}
		else if(delta == 0){
			raiz = -(b) / (2 * a);
			return raiz;
		} 
		else{
			raiz = (-(b) + sqrt(delta)) / (2 * a);
			return raiz;
		}
	} else{
		cout << "\nA equacao nao e do 2 grau!";
	}
	return NULL;
}

int main(){
	float a, b, c, r, h;

	cout << "\nNome: Iago Zagnoli Albergaria";
	cout << "\nMatricula: 2022069473";
	cout << "\n-------------------------------------------------------\n\n";
	
	cout << "Enter a, b, c: ";
	cin >> a >> b >> c;
	
	cout << "\nDigite o raio e a altura respectivamente: ";
	cin >> r >> h;
	
	cout << "\nMedia: " << media(a, b, c);
	cout << "\nMedia ponderada: " << media_ponderada(a, b, c);
	cout << "\nPerimetro do circulo: " << perimetro_circulo(r);
	cout << "\nArea do circulo: " << area_circulo(r);
	cout << "\nArea do triangulo: " << area_triangulo(b,c);
	cout << "\nArea da caixa: " << area_caixa(a, b, c);
	cout << "\nVolume da caixa: " << volume_caixa(a, b, c);
	cout << "\nArea do cilindro: " << area_cilindro(r, h);
	cout << "\nVolume do cilindro: " << volume_cilindro(r, h);
	cout << "\nHipotenusa do triangulo: " << hipotenusa_triangulo(b, c);
	cout << "\nRaiz positiva da equacao do 2 grau: " << raiz_equacao_2_grau(a, b, c) << endl;
}
