// Copyright 2018 Universidade Federal de Minas Gerais (UFMG)

#include "complexo.h"

#include <cmath>

Complexo::Complexo() : Complexo(0, 0) {
}

Complexo::Complexo(double a) : Complexo(a, 0) {
}

Complexo::Complexo(double a, double b) {
    _real = a;
    _imag = b;
}

double Complexo::real() const {
  return _real;
}

double Complexo::imag() const {
  return _imag;
}

bool Complexo::operator==(Complexo x) const {
    return(_real == x.real() && _imag == x.imag());
}

void Complexo::operator=(Complexo x) {
    _real = x.real();
    _imag = x.imag();
} 

double Complexo::modulo() const {
    return(sqrt((_real*_real) + (_imag*_imag)));;
}

Complexo Complexo::conjugado() const {
    return Complexo(_real, -(_imag)); 
}

Complexo Complexo::operator-() const {
  return Complexo(-(_real), -(_imag));
}

Complexo Complexo::inverso() const {
    if(_real == 0) return Complexo(0.0, 1.0/_imag);
    if(_imag == 0) return Complexo(1.0/_real, 0.0);
    return Complexo(1.0/_real, 1.0/_imag);
}

Complexo Complexo::operator+(Complexo y) const {
    return Complexo(_real + y._real, _imag + y._imag);
}

Complexo Complexo::operator-(Complexo y) const {
    return Complexo(_real - y._real, _imag - y._imag);
}

Complexo Complexo::operator*(Complexo y) const {
    return Complexo((_real*y._real) - (_imag*y._imag), 
                    (_real*y._imag) + (_imag*y._real));
}

Complexo Complexo::operator/(Complexo y) const {
    return Complexo(((_real*y._real)+(_imag*y._imag))/(pow(y._real,2)+pow(y._imag,2)),
                    ((_imag*y._real)-(_real*y._imag))/(pow(y._real,2)+pow(y._imag,2)));
}
