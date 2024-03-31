#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Matrix{
    static int n, m;
    static vector<vector<int> > matrix;

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

    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.n; i++) {
            string output;
            for (int j = 0; j < mat.m; j++) {
                output += to_string(mat.matrix[i][j]) + " ";
            }
            output.pop_back();
            output += "\n";
            cout << output;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Matrix& mat) {
        for (int i = 0; i < mat.n; i++) {
            for (int j = 0; j < mat.m; j++) {
                is >> mat.matrix[i][j];
            }
        }
        return is;
    }

    void print(){
        for (int i = 0; i < n; i++){
            string output;
            for (int j = 0; j < m; j++){
                int item = matrix[i][j];
                output += to_string(item) + " ";
            }
            output.pop_back();
            cout << output << "\n";
        }
    }

    static int getN(){
        return n;
    }
    static int getM(){
        return m;
    }
    static vector<vector<int> > getMatrix(){
        return matrix;
    }

    static int getAt(int i, int j){
        return matrix[i][j];
    }

    static void setAt(int i, int j, int value){
        matrix[i][j] = value;
    }

    static bool equals(Matrix other){
        if (getN() == other.getN() && getM() == other.getM()){
            return true;
        }
        return false;
    }

    virtual Matrix& operator=(const Matrix& other){
        if (this != &other) {
            matrix = other.matrix;
            n = other.n;
            m = other.m;
        }
        return *this;
    }

    virtual Matrix operator+ (const Matrix other) const{
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
    virtual Matrix operator- (const Matrix& other) const {
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
    virtual Matrix operator* (const Matrix& other) const{
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
    virtual Matrix transpose() const{
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

protected:
    static int size;
public:
    SquareMatrix(int n) : Matrix(n, n){ this -> size = n;}
    SquareMatrix(int n, vector<vector<int> > matrix) : Matrix(n, n, matrix){}


//    friend ostream& operator<<(ostream& os, const SquareMatrix& mat){
//        for (int i = 0; i < size; i++) {
//            string output;
//            for (int j = 0; j < mat.getN(); j++) {
//                output += to_string(mat.getAt(i, j)) + " ";
//            }
//            output.pop_back();
//            output += "\n";
//            cout << output;
//        }
//        return os;
//    }
//
//    friend istream& operator>>(istream& is, SquareMatrix& mat) {
//        for (int i = 0; i < mat.getN(); i++) {
//            for (int j = 0; j < mat.getN(); j++) {
//                int value;
//                is >> value;
//                mat.setAt(i, j, value);
//            }
//        }
//        return is;
//    }

    SquareMatrix& operator=(const SquareMatrix& other){
        return dynamic_cast<SquareMatrix&>(Matrix::operator=(other));
    }

    SquareMatrix operator+(const SquareMatrix& other) {
        Matrix result = Matrix::operator+(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }

    SquareMatrix operator-(const SquareMatrix& other){
        Matrix result = Matrix::operator-(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }
    SquareMatrix operator*(const SquareMatrix& other){
        Matrix result = Matrix::operator*(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }
    SquareMatrix transpose(){
        Matrix result = Matrix::transpose();
        return SquareMatrix(result.getN(), result.getMatrix());
    }
};


int main() {

    int n;
    cin >> n;
    vector<vector<int> > matrix;
    SquareMatrix matA(n);
    cin >> matA;

    cin >> n;
    SquareMatrix matB(n);
    cin >> matB;

    cin >> n ;
    SquareMatrix matC(n);
    cin >> matC;

    SquareMatrix D = matA + matB;
    cout << D;
    SquareMatrix E = matB - matA;
    cout << E;
    SquareMatrix F = matC * matA;
    cout << F;
    SquareMatrix G = matA.transpose();
    cout << G;
    return 0;
}