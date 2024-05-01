#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
protected:
    vector<vector<double> > mat;
    int rows, cols;

public:
    // Constructor to initialize matrix with given size
    Matrix(int r, int c) : rows(r), cols(c) {
        mat.resize(rows, vector<double>(cols, 0));
    }
    Matrix operator*(Matrix& other) {
        if (cols != other.getRows()) {
            cout << "Error: the dimensional problem occurred" << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, other.getCols());
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.getCols(); ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.set(i,j, result.get(i,j)+mat[i][k] * other.get(k,j));
                }
            }
        }
        return result;
    }
    // Overload cin operator to input matrix
    friend istream& operator>>(istream& in, Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                in >> m.mat[i][j];
            }
        }
        return in;
    }

    // Overload cout operator to output matrix
    friend ostream& operator<<(ostream& out, const Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                out << fixed << setprecision(4) << m.mat[i][j];
                if (j != m.cols - 1) out << " ";
            }
            out << endl;
        }
        return out;
    }

    Matrix transpose() const {
        Matrix result(cols,rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.mat[j][i] = mat[i][j];
            }
        }
        return result;
    }

    // Getter for rows
    int getRows() const {
        return rows;
    }

    // Getter for columns
    int getCols() const {
        return cols;
    }

    // Getter for element at position (i, j)
    double get(int i, int j) const {
        return mat[i][j];
    }

    // Setter for element at position (i, j)
    void set(int i, int j, double value) {
        mat[i][j] = value;
    }

    // Setter for entire row
    void setRow(int index, const vector<double>& row) {
        mat[index] = row;
    }

    // Getter for entire row
    vector<double> getRow(int index) const {
        return mat[index];
    }

    // Swap two rows
    void swapRows(int row1, int row2) {
        swap(mat[row1], mat[row2]);
    }
    void setData(vector<vector<double> > mat){
        this->mat = mat;
    }
    vector<vector<double> > getData(){
        return mat;
    }
};

class SquareMatrix : public Matrix {
public:
    void toSquare (Matrix& other) {
        if (other.getCols() != other.getRows() || other.getRows() != getRows()) {
            cout << "Error: the dimensional problem occurred" << endl;
            return;
        }
        setData(other.getData());
        return;
    }
    SquareMatrix operator*(SquareMatrix& other) {
        if (cols != other.getRows()) {
            cout << "Error: the dimensional problem occurred" << endl;
            return SquareMatrix(0);
        }

        SquareMatrix result(rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.getCols(); ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.set(i,j, result.get(i,j)+mat[i][k] * other.get(k,j));
                }
            }
        }
        return result;
    }
    // Constructor to initialize square matrix with given size
    SquareMatrix(int n) : Matrix(n, n) {}

    // Transpose square matrix
    SquareMatrix transpose() const {
        SquareMatrix result(rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.mat[j][i] = mat[i][j];
            }
        }
        return result;
    }

    // Concat two matrices
    Matrix concat(SquareMatrix mat1) const {
        Matrix result(rows, rows*2);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < rows; ++j) {
                result.set(i, j, mat[i][j]);
                result.set(i, j+rows, mat1.get(i, j));
            }
        }
        return result;
    }
    // Compute the inverse matrix using Gaussian elimination with pivoting
    SquareMatrix inverse() const {
        if (rows != cols) {
            cerr << "Error: Matrix is not square" << endl;
            return SquareMatrix(0);
        }
        // Initialize result
        vector<Matrix> result;
        vector<int> result_type;

        SquareMatrix augmentedMatrix(rows);
        augmentedMatrix.mat = mat;

        SquareMatrix identityMatrix(rows);
        for (int i = 0; i < rows; ++i) {
            identityMatrix.mat[i][i] = 1;
        }

        // Forward elimination
        for (int i = 0; i < rows; ++i) {
            // Pivot for this column
            int maxRow = i;
            for (int j = i + 1; j < rows; ++j) {
                if (abs(augmentedMatrix.mat[j][i]) > abs(augmentedMatrix.mat[maxRow][i])) {
                    maxRow = j;
                }
            }
            if (maxRow != i) {
                augmentedMatrix.swapRows(i, maxRow);
                identityMatrix.swapRows(i, maxRow);
                result_type.push_back(1);
                result.push_back(augmentedMatrix.concat(identityMatrix));
            }

            // Make all rows below this one 0 in current column
            for (int j = i + 1; j < rows; ++j) {
                double factor = augmentedMatrix.mat[j][i] / augmentedMatrix.mat[i][i];
                for (int k = i; k < rows; ++k) {
                    augmentedMatrix.mat[j][k] -= factor * augmentedMatrix.mat[i][k];
                }
                for (int k = 0; k < rows; ++k) {
                    identityMatrix.mat[j][k] -= factor * identityMatrix.mat[i][k];
                }
                // cout << "step #" << i + 2 << ": elimination\n";
                result_type.push_back(0);
                result.push_back(augmentedMatrix.concat(identityMatrix));
            }
        }

        // Backward elimination
        for (int i = rows - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                double factor = augmentedMatrix.mat[j][i] / augmentedMatrix.mat[i][i];
                for (int k = 0; k < rows; ++k) {
                    augmentedMatrix.mat[j][k] -= factor * augmentedMatrix.mat[i][k];
                }
                for (int k = 0; k < rows; ++k) {
                    identityMatrix.mat[j][k] -= factor * identityMatrix.mat[i][k];
                }
                result_type.push_back(0);
                result.push_back(augmentedMatrix.concat(identityMatrix));
            }
        }

        // Diagonal normalization
        for (int i = 0; i < rows; ++i) {
            double factor = augmentedMatrix.mat[i][i];
            for (int j = 0; j < rows; ++j) {
                augmentedMatrix.mat[i][j] /= factor;
                identityMatrix.mat[i][j] /= factor;
            }
        }

        // Check if the original matrix is singular
        for (int i = 0; i < rows; ++i) {
            if (augmentedMatrix.mat[i][i] == 0) {
                cerr << "Error: Matrix is singular" << endl;
                return SquareMatrix(0);
            }
        }
        return identityMatrix;
    }
};

class IdentityMatrix : public SquareMatrix {
public:
    // Constructor to initialize square matrix with given size
    IdentityMatrix(int n) : SquareMatrix(n) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == j) {
                    mat[i][j] = 1;
                } else {
                    mat[i][j] = 0;
                }
            }
        }
    }
};

//#ifdef WIN
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
//#else
#define GNUPLOT_NAME "gnuplot -persist"
// #define GNUPLOT_NAME "/opt/homebrew/Cellar/gnuplot/6.0.0/bin/gnuplot -persist"
//#endif


int main()
{

    //#ifdef WIN32
    // FILE* pipe = _popen(GNUPLOT_NAME, "w");
    //#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
    //#endif

    std::cout << std::setprecision(4) << std::fixed;
    int rowSize;
    cin >> rowSize;

    vector<double> rowA;
    Matrix B(rowSize, 1);
    for (int i = 0; i < rowSize; ++i) {
        double a, b;
        cin >> a >> b;
        rowA.push_back(a);
        B.set(i, 0, b);
    }
    int matrixSize;
    cin >> matrixSize;
    Matrix A(rowSize, matrixSize + 1);
    for (int i = 0; i < rowSize; ++i) {
        A.set(i, 0, 1.0);
        for (int j = 0; j < matrixSize; ++j) {
            A.set(i, j+1, A.get(i,j)*rowA[i]);
        }
    }
    Matrix TEMP = A.transpose();
    cout << "A:" << endl;
    cout << A;
    cout << "A_T*A:" << endl;
    cout << TEMP*A;
    cout << "(A_T*A)^-1:" << endl;
    Matrix P = (TEMP*A);
    SquareMatrix PENIS(P.getCols());
    PENIS.toSquare(P);
    cout << PENIS.inverse(); 
    Matrix *ptr;
    ptr = &TEMP;
    Matrix &ref = TEMP;
    cout << "A_T*b:" << endl;
    Matrix TEMP2 = *ptr*B;
    cout << TEMP2;
    cout << "x~:" << endl;
    SquareMatrix TEMP1 = PENIS.inverse();
    Matrix *ptr1;
    ptr1 = &TEMP1;
    Matrix &ref1 = TEMP1;
    Matrix approximation = *ptr1*TEMP2;
    cout << (*ptr1)*TEMP2;

    if (pipe != NULL){
        string func = "";

        fprintf(pipe, "set xrange [%d: %d]\n", 0, 20);
        fprintf(pipe, "set yrange [%d :%d]\n", 0, 20);

        for (int i = 0; i < matrixSize + 1; i++){
            func += to_string( approximation.get(i, 0));
            func += " * x **" + to_string(i);
            if (i != matrixSize){
                func += "+";
            }
        }

        fprintf(pipe, "plot '-' with points title 'input' pointtype 5, %s with lines title 'approximation' linetype 1\n", func.c_str());

        for (int i = 0; i < rowSize; i++){
            fprintf(pipe, "%f %f\n", rowA[i], B.get(i, 0));
        }

    }


    return 0;
}
