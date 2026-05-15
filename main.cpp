#include <iostream>
#include <random>

class Tensor {
    int rows;
    int cols;
    float* data;

    Tensor* parent1;
    Tensor* parent2;

    public:

    Tensor(int nRows, int nCols) {
        rows = nRows;
        cols = nCols;
        data = new float[nRows * nCols];
    };

    void ToRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

        for(int i = 0; i < rows * cols; i++) {
            data[i] = dist(gen);
        };
    };

    void toZero() {
        for(int i = 0; i < rows * cols; i++) {
            data[i] = 0.0f;
        };
    }

    Tensor(int nRows, int nCols, float* &ptrToData) {
        rows = nRows;
        cols = nCols;
        data = ptrToData;

        for(int i = 0; i < nRows * nCols; i++) {
            data[i] =  ptrToData[i];
        };
    };

    Tensor* getParent1() {
        return parent1;
    }

    Tensor* getParent2() {
        return parent2;
    }

    Tensor* add(Tensor* &tensor) {
        if(rows != tensor->rows || cols != tensor->cols) {
            throw std::invalid_argument("Invalid shape!");
        };

        Tensor* result = new Tensor(rows, cols);
        result->parent1 = this;
        result->parent2 = tensor;

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = data[i] + tensor->data[i];
        }

        return result;
    };

    Tensor* neg() {
        Tensor* result = new Tensor(rows, cols);
        result->parent1 = this;

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = - data[i];
        }

        return result;
    };

    Tensor* scale(float scalar) {
        Tensor* result = new Tensor(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = scalar * data[i];
        };

        return result;
    };

    Tensor* matmul(Tensor* &tensor) {
        if(cols != tensor->rows) {
            throw std::invalid_argument("Invalid shape!");
        };

        Tensor* result = new Tensor(rows, tensor->cols);
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

    Tensor* transpose() {
        Tensor* result = new Tensor(cols, rows);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                result->data[j * result->cols + i] = data[i * cols + j];
            };
        };
        return result;
    };

    Tensor* relu() {
       Tensor* result = new Tensor(rows, cols);
       
       for(int i = 0; i < rows * cols; i++) {
            if(data[i] > 0) {
                result->data[i] = data[i];
            } else {
                result->data[i] = 0.0f;
            }
       };

       return result;
       
    };

    Tensor* tanh();

    Tensor* expo() {
        Tensor* result = new Tensor(rows, cols);

        for(int i = 0; i < rows * cols; i++) {
            result->data[i] = exp(data[i]);
        };

        return result;
    };


    Tensor* max(int axis) {
        if(axis != 0 && axis != 1) {
            throw std::invalid_argument("Invalid axis");
        };

        // (3, 2) -> (3, 1) axis == 0
        // (3, 2) -> (1, 2) axis == 0

        if(axis == 0){
            Tensor* result = new Tensor(rows, 1);

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

        Tensor* result = new Tensor(1, cols);

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

    Tensor* sum();
    Tensor *mean();

    void print() {
        std::cout << "" << std::endl;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                std::cout << data[i * cols + j] << " ";
            };
            std::cout << "" << std::endl;
        }
    };
};

int main() {
    Tensor* test = new Tensor(3, 3);
    test->ToRandom();
    test->print();

    Tensor* t = test->scale(2.0);
    t->print();

    Tensor* m = t->max(0);
    m->print();

    Tensor* m2 = t->max(1);
    m2->print();

    return 0;
};