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

    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            string output;
            for (int j = 0; j < mat.m; ++j) {
                if (j != mat.m - 1){
                    cout << fixed << setprecision(4) << mat.matrix[i][j] << " ";
                } else {
                    cout << fixed << setprecision(4) << mat.matrix[i][j];
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
    int getN(){
        return n;
    }
    int getM(){
        return m;
    }

    vector<vector<double> > getMatrix(){
        return matrix;
    }

    void set(int i, int j, double value){
        matrix[i][j]=value;
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
    Matrix transpose (){
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
    SquareMatrix(int n, vector<vector<double> > matrix) : Matrix(n, n, matrix){}
    
    friend ostream& operator<<(ostream& os, const SquareMatrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            string output;
            for (int j = 0; j < mat.n; ++j) {
                if (j != mat.n - 1){
                    cout << fixed << setprecision(2) << mat.matrix[i][j] << " ";
                } else {
                    cout << fixed << setprecision(2) << mat.matrix[i][j];
                }
            }
            cout << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, SquareMatrix& mat) {
        for (int i = 0; i < mat.n; ++i) {
            for (int j = 0; j < mat.n; ++j) {
                is >> mat.matrix[i][j];
            }
        }
        return is;
    }
    
    SquareMatrix& operator= (const SquareMatrix& other){
        if (this != &other) {
            Matrix::operator=(other);
        }
        return *this;
    }
    SquareMatrix operator+(SquareMatrix& other){
        Matrix result = Matrix::operator+(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }
    SquareMatrix operator-(SquareMatrix& other){
        Matrix result = Matrix::operator-(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }
    SquareMatrix operator*(Matrix& other){
        Matrix result = Matrix::operator*(other);
        return SquareMatrix(result.getN(), result.getMatrix());
    }
    SquareMatrix transpose(){
        Matrix result = Matrix::transpose();
        return SquareMatrix(result.getN(), result.getMatrix());
    }
};

class IdentityMatrix : public SquareMatrix{

public:
    IdentityMatrix(int n) : SquareMatrix(n){
        for (int i = 0; i < n; i++) {
            matrix[i][i] = 1;
        }
    }
    IdentityMatrix& operator= (const SquareMatrix& other){
        return static_cast<IdentityMatrix &>(SquareMatrix::operator=(other));
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

class ColumnVector : public Matrix{

public:
    ColumnVector(int n) : Matrix(n, 1){};
    ColumnVector(int n, vector<vector<double> > matrix) : Matrix(n, 1, matrix){};

    ColumnVector& operator=(const Matrix& other) {
        return static_cast<ColumnVector&>(Matrix::operator=(other));
    }

    friend ostream& operator<<(ostream& os, const ColumnVector& mat){
        for (int i = 0; i < mat.n; ++i) {
            cout << fixed <<setprecision(2) << mat.matrix[i][0] << " ";
        }
        cout << endl;
        return os;
    }

};


double det(Matrix matA, int size){
    int multi = 1;
    double determinant = 1;
    for (int r = 0; r < size; r++){
        int maxRow = r;
        for(int i = r; i < size; i++){
            if (abs(matA.getAt(i, r)) > abs(matA.getAt(maxRow, r))){
                maxRow = i;
            }
        }
        PermutationMatrix matP(size, r+1, maxRow+1);
        Matrix tmp = matP * matA;
        if (!(tmp.isEqual(matA))){
            matA = matP * matA;
            multi *= -1;
        } else{
            matA = matP * matA;
        }

        for (int er = r+1; er <size; er++){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(size, er+1, r+1, r, matA);
                matA = matE * matA;
            }
        }
    }
    for (int i = 0; i < size; i ++){
        determinant *= (matA.getAt(i, i));
    }
    return determinant;
}

void print(Matrix matA, Matrix matB, int sizeA, int sizeB){
    for (int r = 0; r < sizeA; r++){

        for (int c = 0; c < sizeA; c++){
            cout << fixed << setprecision(2) << matA.getAt(r, c) << " ";
        }
        for (int c = 0; c < sizeB; c++){
            cout << fixed << setprecision(2) << matB.getAt(r, c) << " ";
        }
        cout << endl;
    }

}

Matrix inverse(Matrix matA, int n){
    int step = 0;
    IdentityMatrix inverse(n);
    if (det(matA, n) == 0){
        return inverse;
    }
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
            inverse = matP * inverse;
            matA = matP * matA;
            step++;
        } else{
            matA = matP * matA;
        }

        for (int er = r+1; er <n; er++){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(n, er+1, r+1, r, matA);
                inverse = matE * inverse;
                matA = matE * matA;
                step++;
            }
        }
    }

    for (int r = n-1; r > 0; r--){
        for (int er = r - 1; er >= 0; er--){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(n, er+1, r+1, r, matA);
                inverse = matE * inverse;
                matA = matE * matA;
                step++;
            }
        }
    }
    for (int i = 0; i < n; i++){
        double multiplier = 1 / matA.getAt(i, i);
        for (int j = 0; j < n; j++){
            inverse.set(i, j, inverse.getAt(i, j) * multiplier);
            matA.set(i, j, matA.getAt(i, j) * multiplier);
        }
    }

    return inverse;
}

void SolvingSLAE(Matrix matA, ColumnVector vectorB, int sizeA, int sizeB){
    int step = 0;
    int n = sizeA;
    
    if (det(matA, n) == 0){
        return;
    }

    cout << "Gaussian process:\n";
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
            vectorB = matP * vectorB;
            matA = matP * matA;
            step++;
        } else{
            matA = matP * matA;
        }

        for (int er = r+1; er <n; er++){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(n, er+1, r+1, r, matA);
                vectorB = matE * vectorB;
                matA = matE * matA;
                step++;
            }
        }
    }

    for (int r = n-1; r > 0; r--){
        for (int er = r - 1; er >= 0; er--){
            if (matA.getAt(er, r)!=0){
                EliminationMatrix matE(n, er+1, r+1, r, matA);
                vectorB = matE * vectorB;
                matA = matE * matA;
                step++;
            }
        }
    }
    for (int i = 0; i < n; i++){
        double multiplier = 1 / matA.getAt(i, i);
        for (int j = 0; j < n; j++){
            if (matA.getAt(i, j) != 0) {
                matA.set(i, j, (matA.getAt(i, j) * multiplier));
            }
            else { continue;}
        }
        if (vectorB.getAt(i, 0) != 0) {
            vectorB.set(i, 0,  multiplier * vectorB.getAt(i, 0));
        } else { continue;}

    }
}

int main() {
    int step=0;
    int n;
    cin >> n;
    vector<vector<double> > input = vector<vector<double> >(n, vector<double>(2));
    for (int i = 0; i < n; i++){
        double t, b;
        cin >> t >> b;
        // input.push_back(vector<double>(2));
        input[i][0] = t;
        input[i][1] = b;
    }
    int k;
    cin >> k;
    
    Matrix matA(n, k+1);    
    ColumnVector vectorB(n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < k+1; j++){
            matA.set(i, j, pow(input[i][0], j));
        }
        vectorB.set(i, 0, input[i][1]);
    }

    cout << "A:\n";
    cout << matA;
    
    Matrix matAT = matA.transpose();
    Matrix matATmatA = matAT * matA;
    cout << "A^T*A:\n";
    cout << matATmatA;
    Matrix inverseA = inverse(matATmatA, k+1);
    cout << "(A^T*A)^-1:\n";
    cout << inverseA;
    Matrix matATb = matAT * vectorB;
    cout << "A^T*b:\n";
    cout << matATb;
    Matrix x = inverseA * matATb;
    cout << "x~:\n";
    cout << x;

    return 0;
}
