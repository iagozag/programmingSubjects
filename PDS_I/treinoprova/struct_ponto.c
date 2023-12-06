#include <stdio.h>
#include <math.h>
#include <stdbool.h>

struct Ponto{
    float x, y;
    void atribuir(float a, float b);
    float distancia(Ponto& p);
    void imprime();
};

struct Triangulo{
    Ponto v1, v2, v3;
    float perimetro();
    float area();
    bool equilatero();
    void angulo(float* angulos);
    bool semelhante(Triangulo& t);
};

struct Retangulo{
    Ponto v1, v2, v3, v4;
    bool valido();
    float perimetro();
    float area();
    bool quadrado();
};

struct Circunferencia{
    Ponto c;
    float raio;
    void atribuir(float x);
    float perimetro();
    float area();
    bool contem(Ponto& p);
    bool contem(Triangulo& t);
    bool contem(Retangulo& r);
    bool pertence(Ponto& p);
    bool circunscrita(Triangulo& t);
    bool circunscrita(Retangulo& r);
};

//PONTO
float Ponto::distancia(Ponto& p){
    return(sqrt((x - p.x) * (x - p.x) + ((y - p.y) * (y - p.y))));
}

void Ponto::atribuir(float a, float b){
    x = a;
    y = b;
}

//TRIANGULO
float Triangulo::perimetro(){
    return(v1.distancia(v2) + v1.distancia(v3) + v2.distancia(v3));
}

float Triangulo::area(){
    float p = (this->perimetro()) / 2;
    return(sqrt(p * (p - v1.distancia(v2)) * (p - v1.distancia(v3)) * (p - v2.distancia(v3))));
}

bool Triangulo::equilatero(){
    return((v1.distancia(v2) == v1.distancia(v3)) && (v1.distancia(v2) == v2.distancia(v3)));
}

void Triangulo::angulo(float* angulos){
    float l1 = v1.distancia(v2);
    float l2 = v1.distancia(v3);
    float l3 = v2.distancia(v3);
    angulos[0] = ((l1 * l1) - (l2 * l2) - (l3 * l3)) / (-2 * (l2 * l3));
    angulos[1] = ((l2 * l2) - (l1 * l1) - (l3 * l3)) / (-2 * (l1 * l3));
    angulos[2] = ((l3 * l3) - (l1 * l1) - (l2 * l2)) / (-2 * (l1 * l2));
}

bool Triangulo::semelhante(Triangulo& t){
    float angulos1[3], angulos2[3];
    angulo(angulos1);
    t.angulo(angulos2);
    int k = 0;
    for(int i = 0; i < 3; i++){
        if(k >= 2) return(true);
        for(int j = 0; j < 3; j++){
            if(angulos1[i] == angulos2[j]){
                k++;
                break;
            }
        }
    }
    return(false);
}

//RETANGULO
bool Retangulo::valido(){
    return(v1.x == v4.x && v1.y == v2.y && v2.x == v3.x && v4.y == v3.y);
}

float Retangulo::perimetro(){
    return(v1.distancia(v2) + v2.distancia(v3) + v3.distancia(v4) + v4.distancia(v1));
}

float Retangulo::area(){
    return(v1.distancia(v2) * v2.distancia(v3));
}
bool Retangulo::quadrado(){
    return(valido() && (this->perimetro() - (4 * v1.distancia(v2)) == 0));
}

//CIRCUNFERENCIA
void Circunferencia::atribuir(float x){
    raio = x;
}

float Circunferencia::perimetro(){
    return(2 * M_PI * raio);
}

float Circunferencia::area(){
    return(M_PI * raio * raio);
}

bool Circunferencia::contem(Ponto& p){
    return(c.distancia(p) < raio);
}

bool Circunferencia::contem(Triangulo& t){
    return(this->contem(t.v1) && this->contem(t.v2) && this->contem(t.v3));
}

bool Circunferencia::contem(Retangulo& r){
    return(this->contem(r.v1) && this->contem(r.v2) && this->contem(r.v3) && this->contem(r.v4));
}

bool Circunferencia::pertence(Ponto& p){
    return(c.distancia(p) == raio);
}

bool Circunferencia::circunscrita(Triangulo& t){
    return(this->pertence(t.v1) && this->pertence(t.v2) && this->pertence(t.v3));
}

bool Circunferencia::circunscrita(Retangulo& r){
    return(this->pertence(r.v1) && this->pertence(r.v2) && this->pertence(r.v3) && this->pertence(r.v4));
}

int main(){
    Ponto p1, p2;
    p1.atribuir(0, 1);
    p2.atribuir(1, 2);
    printf("distancia: %f\n", p1.distancia(p2));

    Triangulo t1, t2;
    t1.v1.atribuir(0, 0);
    t1.v2.atribuir(0, 1);
    t1.v3.atribuir(-0.8660254037844, 0.5);
    t2.v1.atribuir(0, 0);
    t2.v2.atribuir(0, 2);
    t2.v3.atribuir(-1.7320508075688, 1);
    printf("\nperimetro triangulo: %f\n", t1.perimetro());
    printf("area triangulo: %f\n", t1.area());
    printf("triangulo equilatero: %d\n", t1.equilatero());
    printf("triangulo semelhante: %d\n", t1.semelhante(t2));

    Retangulo r1;
    r1.v1.atribuir(1, 0);
    r1.v2.atribuir(2, 0);
    r1.v3.atribuir(2, 1);
    r1.v4.atribuir(1, 1);
    printf("\nretangulo valido: %d\n", r1.valido());
    printf("perimetro retangulo: %f\n", r1.perimetro());
    printf("area retangulo: %f\n", r1.area());
    printf("retangulo quadrado: %d\n", r1.quadrado());

    Circunferencia c1;
    c1.c.atribuir(0, 0);
    c1.atribuir(1);
    printf("\nperimetro circunferencia: %f\n", c1.perimetro());
    printf("area circunferencia: %f\n", c1.area());
    printf("circunferencia contem o ponto: %d\n", c1.contem(p1));
    printf("circunferencia contem o triangulo: %d\n", c1.contem(t1));
    printf("circunferencia contem o retangulo: %d\n", c1.contem(r1));
    printf("ponto pertence a circunferencia: %d\n", c1.pertence(p1));
    printf("circunferencia eh circunscrita no triangulo: %d\n", c1.circunscrita(t1));
    printf("circunferencia eh circunscrita no retangulo: %d\n", c1.circunscrita(r1));

    return(0);
}
