#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


class Matrix{
protected:
    int n, m;
    vector<vector<double> > matrix;
public:
    Matrix(int n, int m){
        this -> n = n;
        this -> m = m;
        matrix.resize(n, vector<double>(m, 0));
    }
    Matrix(int n, int m, vector<vector<double> > matrix){
        this -> n = n;
        this -> m = m;
        this -> matrix = matrix;
    }
    vector<vector<double> > getMatrix(){
        return matrix;
    }
    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            string output;
            for (int j = 0; j < mat.m; ++j) {
                if (j != mat.m - 1){
                    cout << fixed << setprecision(2) << mat.matrix[i][j] << " ";
                } else {
                    cout << fixed << setprecision(2) << mat.matrix[i][j];
                }
            }
            cout << endl;
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

    double getAt(int i, int j){
        return matrix[i][j];
    }

    bool equals(Matrix other){
        if (n == other.n && m == other.m){
            return true;
        }
        return false;
    }

    bool isEqual(Matrix other){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (matrix[i][j] != other.getAt(i, j))return false;
            }
        }
        return true;
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
        vector<vector<double> > newMatrix;
        if (equals(other)){
            for (int i = 0; i < n; i++){
                vector<double> tmp;
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
        vector<vector<double> > newMatrix;
        if (equals(other)){
            for (int i = 0; i < n; i++){
                vector<double> tmp;
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
        vector<vector<double> > newMatrix;
        if (m == other.n){
            for (int i = 0; i < n; i++){
                vector<double> tmp;
                newMatrix.push_back(tmp);
                for (int j = 0; j < other.m; j++){
                    double value = 0;
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
        vector<vector<double> > newMatrix;
        for (int i = 0; i < m; i++){
            vector<double> row;
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

    SquareMatrix& operator=(const SquareMatrix& other) {
        if (this != &other) {
            matrix = other.matrix;
            n = other.n;
            m = other.m;
        }
        return *this;
    }
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
    EliminationMatrix(int n, int i1, int i2, int index,  Matrix mat) : IdentityMatrix(n){

        double a = mat.getAt(i2 - 1, index);
        double b = mat.getAt(i1 - 1, index);
        double number = ((double)(b / a)) * -1;
        matrix[i1-1][index] = number;
    }

};

class PermutationMatrix : public IdentityMatrix {
public:
    PermutationMatrix(int n, int i1, int i2) : IdentityMatrix(n) {
        int tmp;
        for (int i = 0; i < m; i++){
            tmp = getAt(i1-1, i);
            matrix[i1-1][i] = getAt(i2-1, i);
            matrix[i2-1][i] = tmp;
        }
    }

};

double det(Matrix matA, int size){
    double determinant = 1;
    for (int i = 0; i < size; i ++){
        determinant *= (matA.getAt(i, i));
    }
    return determinant;
}

int main() {
    int step=0;
    int n;
    int multi = 1;
    cin >> n;
    vector<vector<int> > matrix;
    Matrix matA(n, n);
    cin >> matA;
    for (int r = 0; r < n; r++){
        int maxRow = r;
        for(int i = r; i < n; i++){
            if (abs(matA.getAt(i, r)) > abs(matA.getAt(maxRow, r))){
                maxRow = i;
            }
        }
        PermutationMatrix matP(n, r+1, maxRow+1);
        Matrix tmp = matP * matA;
        if (!(tmp.isEqual(matA))){
            matA = matP * matA;
            step++;
            cout << "step #" << step << ": permutation\n";
            cout << matA;
            multi *= -1;
        } else{
            matA = matP * matA;
        }
        for (int er = r+1; er <n; er++){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(n, er+1, r+1, r, matA);
                matA = matE * matA;
                step++;
                cout << "step #" << step << ": elimination\n";
                cout << matA;
            }

        }
    }


    cout << "result:\n";
    cout << fixed << setprecision(2) << det(matA, n) * multi;


    return 0;
}
