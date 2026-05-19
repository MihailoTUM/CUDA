#include <iostream>
#include <random>
#include "Tensor.h"
#include "Matrix.h"
#include <set>
#include <vector>

Tensor::Tensor(int nRows, int nCols) {
    data = new Matrix(nRows, nCols);
};

Tensor::Tensor(int nRows, int nCols, Tensor* tensor){
    data = new Matrix(nRows, nCols, tensor->data->getData());
}

Matrix* Tensor::getData() {
    return data;
}

Matrix* Tensor::getGrads() {
    return grads;
}

Tensor* Tensor::getParent1() {
    return parent1;
}

Tensor* Tensor::getParent2() {
    return parent2;
}

void Tensor::addBackward(Tensor* tensor) {
    if(tensor->grads == nullptr) {
        // create new Matrix
        tensor->grads = new Matrix(tensor->data->getRows(), tensor->data->getCols());
        tensor->grads->toOne();
    };

    tensor->getParent1()->grads = tensor->grads;
    tensor->getParent2()->grads = tensor->grads;
};

Tensor* Tensor::operator+(Tensor* tensor) {
    if(data->getRows() != tensor->data->getRows() || data->getCols() != tensor->data->getCols()) {
        throw std::invalid_argument("Invalid shapes");
    };

    Tensor* result = new Tensor(data->getRows(), data->getCols());
    result->data = data->add(tensor->data);
    result->parent1 = this;
    result->parent2 = tensor;

    result->_backward = [result](Tensor *t) {
        result->addBackward(result);
    };

    return result;
};

bool Tensor::inVisited(Tensor* tensor, std::set<Tensor*>& visited) {
    if(auto search = visited.find(tensor); search != visited.end()) {
        return true;
    };
    return false;
};

void Tensor::createTree(Tensor* tensor, std::set<Tensor*>& visited) {
    if(tensor->getParent1() != nullptr && !inVisited(tensor->getParent1(), visited)) {
        visited.insert(tensor);
        createTree(tensor->getParent1(), visited);
    };
    // parent2
    // add to tree after parent2 checked
};

void Tensor::backward() {
    std::set<Tensor*> visited;
    std::vector<Tensor*> tree;


};