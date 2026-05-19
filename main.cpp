#include "Matrix.h"
#include "Tensor.h"
#include <iostream>

int main() {
    Tensor* t1 = new Tensor(3, 3);
    t1->getData()->ToRandom();
    t1->getData()->print();

    Tensor* t2 = new Tensor(3, 3);
    t2->getData()->ToRandom();
    t2->getData()->print();
    
    return 0;
}