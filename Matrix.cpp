#include <iostream>
#include <random>
#include "Matrix.h"


    Matrix::Matrix(int nRows, int nCols) {
        rows = nRows;
        cols = nCols;
        data = new float[nRows * nCols];
    };

    Matrix::Matrix(int nRows, int nCols, float* ptrToData) {
        rows = nRows;
        cols = nCols;
        data = ptrToData;

        for(int i = 0; i < nRows * nCols; i++) {
            data[i] =  ptrToData[i];
        };
    };

    float* Matrix::getData() {
        return data;
    }

    int Matrix::getRows() {
        return rows;
    }

    int Matrix::getCols() {
        return cols;
    }

    void Matrix::ToRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        for(int i = 0; i < rows * cols; i++) {
            data[i] = dist(gen);
        };
    };

    void Matrix::toZero() {
        for(int i = 0; i < rows * cols; i++) {
            data[i] = 0.0f;
        };
    };

    void Matrix::toOne() {
        for(int i = 0; i < rows * cols; i++) {
            data[i] = 1.0f;
        };
    };

    Matrix* Matrix::add(Matrix* tensor) {
        if(rows != tensor->rows || cols != tensor->cols) {
            throw std::invalid_argument("Invalid shape!");
        };

        Matrix* result = new Matrix(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = data[i] + tensor->data[i];
        }

        return result;
    };

    Matrix* Matrix::neg() {
        Matrix* result = new Matrix(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = - data[i];
        }

        return result;
    };

    Matrix* Matrix::scale(float scalar) {
        Matrix* result = new Matrix(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = scalar * data[i];
        };

        return result;
    };

    Matrix* Matrix::matmul(Matrix* tensor) {
        if(cols != tensor->rows) {
            throw std::invalid_argument("Invalid shape!");
        };

        Matrix* result = new Matrix(rows, tensor->cols);
        result->toZero();

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                for(int m = 0; m < cols; m++) {
                    result->data[i + j * tensor->cols] += data[i * cols + m] * tensor->data[m * tensor->cols + j];
                };
            };
        }
        return result;

    };

    Matrix* Matrix::transpose() {
        Matrix* result = new Matrix(cols, rows);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                result->data[j * result->cols + i] = data[i * cols + j];
            };
        };
        return result;
    };

    Matrix* Matrix::relu() {
       Matrix* result = new Matrix(rows, cols);
       
       for(int i = 0; i < rows * cols; i++) {
            if(data[i] > 0) {
                result->data[i] = data[i];
            } else {
                result->data[i] = 0.0f;
            }
       };

       return result;
       
    };

    Matrix* Matrix::tanh() {
        return nullptr;
    }

    Matrix* Matrix::expo() {
        Matrix* result = new Matrix(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = exp(data[i]);
        };

        return result;
    };

    Matrix* Matrix::max(int axis) {
        if(axis != 0 && axis != 1) {
            throw std::invalid_argument("Invalid axis");
        };

        // (3, 2) -> (3, 1) axis == 0
        // (3, 2) -> (1, 2) axis == 0

        if(axis == 0){
            Matrix* result = new Matrix(rows, 1);

            for(int i = 0; i < rows; i++) {
                float maxRows = data[i * cols];

                for(int j = 0; j < cols; j++) {
                    if(data[i * cols + j] > maxRows) {
                        maxRows = data[i * cols + j];
                    };
                };

                result->data[i] = maxRows;
            };

            return result;
        };

        Matrix* result = new Matrix(1, cols);

        for(int i = 0; i < cols; i++) {
            float maxCols = data[i];
            
            for(int j = 0; j < cols; j++) {
                if(data[i + cols * j] > maxCols) {
                    maxCols = data[i + cols * j];
                }
            };
            result->data[i] = maxCols;
        }

        return result;
    };

    Matrix* Matrix::sum(int axis) {
        if(axis != 0 && axis != 1) {
            throw std::invalid_argument("Invalid axis");
        };

        // (3, 2) -> (3, 1) axis == 0
        // (3, 2) -> (1, 2) axis == 0

        if(axis == 0) {
            Matrix* result = new Matrix(rows, 1);
            float rowSum = 0;

            for(int i = 0; i < rows; i++) {
                rowSum = 0;

                for(int j = 0; j < cols; j++) {
                    rowSum += data[i * cols + j];
                };

                result->data[i] = rowSum;
            };

            return result;
        }

        Matrix* result = new Matrix(1, cols);
        float colSum = 0;

        for(int j = 0; j < cols; j++) {
            colSum = 0;

            for(int i = 0; i < rows; i++) {
                colSum += data[i * cols + j];
            };

            result->data[j] = colSum;
        };
        return result;
    };

    Matrix* Matrix::mean(int axis) {
        if(axis != 0 && axis != 1) {
            throw std::invalid_argument("Invalid axis");
        };

        float meanValue = 0;

        if(axis == 0) {
            Matrix* result = new Matrix(rows, 1);

            for(int i = 0; i < rows; i++) {
                meanValue = 0;

                for(int j = 0; j < cols; j++) {
                    meanValue += data[i * cols + j];
                };
                result->data[i] = meanValue / cols;
            };
            return result;
        };

        Matrix* result = new Matrix(1, cols);

        for(int j = 0; j < cols; j++) {
            meanValue = 0;

            for(int i = 0; i < rows; i++) {
                meanValue += data[i * cols + j];
            };
            result->data[j] = meanValue / rows;
        };

        return result;
    };    
    
    void Matrix::print() {
        std::cout << "" << std::endl;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                std::cout << data[i * cols + j] << " ";
            };
            std::cout << "" << std::endl;
        }
    };