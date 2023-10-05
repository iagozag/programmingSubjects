#include<bits/stdc++.h>
using namespace std;

class Account{
    private:
        string _name;
        unsigned int _balance;

    public:
        Account(string name){
            _name = name;
            _balance = 0;
        }

        bool withdraw(unsigned int value){
            if(value > _balance) return false;
            
            _balance -= value; 
            return true;
        }

        void deposit(unsigned int value){
            _balance += value;
        }

        string get_name(){
            return _name;
        }
        unsigned int get_balance(){
            return _balance;
        }
};

int main(){
    Account account = Account("Iago");

    cout << account.get_name() << endl;
    account.deposit(800);
    cout << account.get_balance() << endl;
    account.withdraw(350);
    cout << account.get_balance() << endl;


    exit(0);
}
