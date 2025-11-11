#include<bits/stdc++.h>
using namespace std;

#define pb push_back

class Matrix{
    private:
        unsigned int _lines;
        unsigned int _colums;
        vector<vector<float>> _matrix;
    
    public:
        Matrix(unsigned int lines, unsigned int colums){
            _lines = lines;
            _colums = colums;
        
            for(int i = 0; i < lines; i++){
                vector<float> data;
                _matrix.pb(data);

                for(int j = 0; j < colums; j++)
                    _matrix[i].pb(0);
            }
        }

        void add_data(int line, int column, float value){
            _matrix[line][column] = value;
        }

        Matrix sum(Matrix a){
            Matrix ans = Matrix(3, 3);
            for(int i = 0; i < this->_lines; i++){
                for(int j = 0; j < this->_colums; j++){
                    ans._matrix[i][j] = this->_matrix[i][j] + a._matrix[i][j];
                }
            }
            return ans;
        }

        void print_matrix(){
            for(int i = 0; i < _lines; i++){
                for(int j = 0; j < _colums; j++){
                    cout << _matrix[i][j] << " ";
                }
                cout << "\n";
            }
        }
};

int main(){
    Matrix m = Matrix(3, 3);
    Matrix n = Matrix(3, 3);
    m.add_data(0, 0, 2);
    m.add_data(2, 2, 5);
    m.print_matrix();
    cout << "\n";

    n.add_data(2, 2, 4);
    n.add_data(1, 2, 9);
    n.print_matrix();
    cout << "\n";

    Matrix ans = m.sum(n);
    ans.print_matrix();
    exit(0);
}
