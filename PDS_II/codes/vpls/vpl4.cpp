#include<bits/stdc++.h>
using namespace std;

class Complexo {
    private:
        double _real;
        double _imag;

    public:
        Complexo(double real, double imag){
            _real = real;
            _imag = imag;
        }

        double modulo() {
            return(sqrt((_real*_real) + (_imag*_imag)));
        }

        Complexo conjugado() {
            Complexo ans = Complexo(this->_real, -(this->_imag));
            return ans; 
        }

        Complexo inverso() {
            Complexo ans = Complexo(1/this->_real, 1/this->_imag);
            return ans;
        }

        Complexo soma(Complexo y) {
            Complexo ans = Complexo(this->_real + y._real, this->_imag + y._imag);
            return ans;
        }

        Complexo subtrair(Complexo y) {
            Complexo ans = Complexo(this->_real - y._real, this->_imag - y._imag);
            return ans;
        }

        Complexo multiplicar(Complexo y) {
            Complexo ans = Complexo((this->_real*y._real) - (this->_imag*y._imag), 
                                    (this->_real*y._imag) + (this->_imag*y._real));
            return ans;
        }

        Complexo dividir(Complexo y) {
            Complexo ans = Complexo(((this->_real*y._real)+(this->_imag*y._imag))/(pow(y._real,2)+pow(y._imag,2)),
                                    ((this->_imag*y._real)-(this->_real*y._imag))/(pow(y._real,2)+pow(y._imag,2)));
            return ans;
        }

        double get_real(){
            return _real;
        }

        double get_imag(){
            return _imag;
        }
};

pair<Complexo, Complexo> raizes(double a, double b, double c) {
    double delta = (b*b) - 4*a*c;
    if(delta < 0){
        Complexo r1 = Complexo(-(b)/(2*a), (sqrt(-delta)) / (2*a));
        Complexo r2 = Complexo(-(b)/(2*a), -((sqrt(-delta)) / (2*a)));
        return(make_pair(r1, r2));
    }

    Complexo r1 = Complexo((-(b) + sqrt(delta))/(2*a), 0);
    Complexo r2 = Complexo((-(b) - sqrt(delta))/(2*a), 0);
    return(make_pair(r1, r2));
}

int main(){
    cout << "Digite os coeficientes da equação f(x) = ax^2 + bx + c:" << endl;
    double a, b, c; cin >> a >> b >> c;
    auto r = raizes(a, b, c);
    cout << "(" << r.first.get_real() << ", " << r.first.get_imag() << ") "
         << "(" << r.second.get_real() << ", " << r.second.get_imag() << ")" << endl;

    return 0;
}
