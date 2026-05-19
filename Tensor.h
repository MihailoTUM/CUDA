#include "Matrix.h"
#include <functional>

#ifndef TENSOR_H
#define TENSOR_H

class Tensor {
    Matrix* data;
    Matrix* grads;

    Tensor* parent1;
    Tensor* parent2;

    public:
        std::function<void(Tensor*)> _backward;

        Tensor(int nRows, int nCols);
        Tensor(int nRows, int nCols, Tensor* tensor);

        Matrix* getData();
        Matrix* getGrads();

        Tensor* getParent1();
        Tensor* getParent2();

        void addBackward(Tensor* tensor);
        Tensor* operator+(Tensor* tensor);

        Tensor* operator*(Tensor* tensor);

        void backward();

};

#endif