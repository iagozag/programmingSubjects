#include<bits/stdc++.h>
using namespace std;

int mdc(int a, int b){
    if(b > a) swap(a, b);
    if(b == 0) return a;
    return mdc(b, a%b);
}

int mmc(int a, int b){
    if(mdc(a, b) == 1) return(a * b);
    if(a < b) swap(a, b);
    return(mmc(a, b/mdc(a, b)));
}

class Fraction{
    private:
        int _numerator;
        int _denominator;

    public:
        Fraction(int numerator, int denominator){
            _numerator = numerator;
            _denominator = denominator;
        }

        Fraction multiplication(int n){
            Fraction ans(this->_numerator * n, this->_denominator);
            return(ans);
        }
        
        Fraction multiplication(Fraction f){
            Fraction ans = Fraction(this->_numerator * f._numerator, this->_denominator * f._denominator);
            return(ans);
        }

        Fraction division(int n){
            Fraction ans(this->_numerator, this->_denominator * n);
            return(ans);
        }
        
        Fraction division(Fraction f){
            Fraction ans = Fraction(this->_numerator * f._denominator, this->_denominator * f._numerator);
            return(ans);
        }

        Fraction sum(int n){
            Fraction ans(this->_numerator + (n*this->_denominator), this->_denominator);
            return(ans);
        }
        
        Fraction sum(Fraction f){
            int mdcfrac = mdc(this->_denominator, f._denominator);
            int mmcfrac = mmc(this->_denominator, f._denominator);
            Fraction ans = Fraction(this->_numerator*f._denominator/mdcfrac + f._numerator*this->_denominator/mdcfrac, mmcfrac);
            return(ans);
        }

        Fraction subtraction(int n){
            Fraction ans(this->_numerator - (n*this->_denominator), this->_denominator);
            return(ans);
        }
        
        Fraction subtraction(Fraction f){
            int mdcfrac = mdc(this->_denominator, f._denominator);
            int mmcfrac = mmc(this->_denominator, f._denominator);
            Fraction ans = Fraction(this->_numerator*f._denominator/mdcfrac - f._numerator*this->_denominator/mdcfrac, mmcfrac);
            return(ans);
        }

        void print_fraction(){
            cout << _numerator << "/" << _denominator << "\n";
        }
};

int main(){
    Fraction f = Fraction(2, 3);
    Fraction g = Fraction(1, 4);
    
    f.print_fraction();
    g.print_fraction();
    cout << "\n";

    cout << "Multiplication: " << "\n";
    Fraction ans = f.multiplication(2);
    ans.print_fraction();
    ans = f.multiplication(g);
    ans.print_fraction();


    cout << "\nDivision: " << "\n";
    ans = f.division(2);
    ans.print_fraction();
    ans = f.division(g);
    ans.print_fraction();

    cout << "\nSum: " << "\n";
    ans = f.sum(2);
    ans.print_fraction();
    ans = f.sum(g);
    ans.print_fraction();

    cout << "\nSubtraction: " << "\n";
    ans = f.subtraction(2);
    ans.print_fraction();
    ans = f.subtraction(g);
    ans.print_fraction(); 

    exit(0);
}
