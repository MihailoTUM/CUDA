
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    int rows;
    int cols;   
    float* data;

    public:
    Matrix(int nRows, int Cols);
    Matrix(int nRows, int Cols, float* ptrToData);

    float* getData();
    int getRows();
    int getCols();

    void ToRandom();
    void toZero();
    void toOne();

    Matrix* add(Matrix* tensor);
    Matrix* neg();
    Matrix* scale(float scalar);
    Matrix* matmul(Matrix* tensor);
    Matrix* transpose();
    Matrix* relu();
    Matrix* tanh();
    Matrix* expo();
    Matrix* max(int axis);
    Matrix* sum(int axis);
    Matrix* mean(int axis);

    void print();
};

#endif