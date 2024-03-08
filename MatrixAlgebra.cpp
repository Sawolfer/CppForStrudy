#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Matrix{
protected:
    int n, m;
    vector<vector<int> > matrix;
public:
    Matrix(int n, int m){
        this -> n = n;
        this -> m = m;
        matrix.resize(n, vector<int>(m, 0));
    }
    Matrix(int n, int m, vector<vector<int> > matrix){
        this -> n = n;
        this -> m = m;
        this -> matrix = matrix;
    }
    vector<vector<int> > getMatrix(){
        return matrix;
    }
    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            string output;
            for (int j = 0; j < mat.m; ++j) {
                output += to_string(mat.matrix[i][j]) + " ";
            }
            output.pop_back();
            output += "\n";
            cout << output;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Matrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            for (int j = 0; j < mat.m; ++j) {
                is >> mat.matrix[i][j];
            }
        }
        return is;
    }

    int getAt(int i, int j){
        return matrix[i][j];
    }

    bool equals(Matrix other){
        if (n == other.n && m == other.m){
            return true;
        }
        return false;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            matrix = other.matrix;
            n = other.n;
            m = other.m;
        }
        return *this;
    }

    Matrix operator+ (Matrix& other){
        vector<vector<int> > newMatrix;
        if (equals(other)){
            for (int i = 0; i < n; i++){
                vector<int> tmp;
                newMatrix.push_back(tmp);
                for (int j = 0; j < m; j++){
                    newMatrix[i].push_back(matrix[i][j] + other.getAt(i, j));
                }
            }
            Matrix toreturn(n, m, newMatrix);
            return toreturn;
        } else {
            cout << "Error: the dimensional problem occurred\n";
        }
        return Matrix(0, 0, newMatrix);
    }
    Matrix operator- (Matrix& other){
        vector<vector<int> > newMatrix;
        if (equals(other)){
            for (int i = 0; i < n; i++){
                vector<int> tmp;
                newMatrix.push_back(tmp);
                for (int j = 0; j < m; j++){
                    newMatrix[i].push_back(matrix[i][j] - other.getAt(i, j));
                }
            }
            Matrix toreturn(n, m, newMatrix);
            return toreturn;
        } else {
            cout << "Error: the dimensional problem occurred\n";
        }
        return Matrix(0, 0, newMatrix);

    }
    Matrix operator* (Matrix& other){
        vector<vector<int> > newMatrix;
        if (m == other.n){
            for (int i = 0; i < n; i++){
                vector<int> tmp;
                newMatrix.push_back(tmp);
                for (int j = 0; j < other.m; j++){
                    int value = 0;
                    for (int k = 0; k < m; k++){
                        value += getAt(i, k) * other.getAt(k, j);
                    }
                    newMatrix[i].push_back(value);
                }
            }
            Matrix toreturn(n, other.m, newMatrix);
            return toreturn;
        } else {
            cout << "Error: the dimensional problem occurred\n";
        }
        return Matrix(0, 0, newMatrix);

    }
    Matrix T (){
        vector<vector<int> > newMatrix;
        for (int i = 0; i < m; i++){
            vector<int> row;
            newMatrix.push_back(row);
            for (int j = 0; j < n; j++){
                newMatrix[i].push_back(getAt(j, i));
            }
        }
        Matrix toReturn(m, n, newMatrix);
        return toReturn;
    }
};

class SquareMatrix : public Matrix{

public:
    SquareMatrix(int n) : Matrix(n, n){}

};

class IdentityMatrix : public SquareMatrix{

public:
    IdentityMatrix(int n) : SquareMatrix(n){
        for (int i = 0; i < n; i++) {
            matrix[i][i] = 1;
        }
    }
};

class EliminationMatrix : public IdentityMatrix{

public:
    EliminationMatrix(int n, int i1, int i2, Matrix mat) : IdentityMatrix(n){

        int a = mat.getAt(i2 - 1, 0);
        int b = mat.getAt(i1 - 1, 0);
        int number = (b / a) * -1;
        matrix[i1-1][i2-1] = number;
    }

};

class PermutationMatrix : public IdentityMatrix {
public:
    PermutationMatrix(int n, int m, int i1, int i2) : IdentityMatrix(n) {
        int tmp;
        for (int i = 0; i < m; i++){
            tmp = getAt(i1-1, i);
            matrix[i1-1][i] = getAt(i2-1, i);
            matrix[i2-1][i] = tmp;
        }
    }

};

int main() {

    int n;
    cin >> n;
    vector<vector<int> > matrix;
    SquareMatrix matA(n);
    cin >> matA;

    IdentityMatrix matI(3);

    EliminationMatrix matE(n, 2, 1, matA);

    Matrix matB = matE * matA;

    PermutationMatrix matP (n, n, 2, 1);

    Matrix matC = matP * matA;

    cout << matI;
    cout << matE;
    cout << matB;
    cout << matP;
    cout << matC;


    return 0;
}



