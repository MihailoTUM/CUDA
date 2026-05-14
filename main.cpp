

class Tensor {
    int rows;
    int cols;
    float* data;

    public:

    Tensor(int nRows, int nCols) {
        rows = nRows;
        cols = nCols;
        data = new float[nRows * nCols];

        for(int i = 0; i < nRows * nCols; i++) {
            data[i] = 0;
        };
    };

    Tensor(int nRows, int nCols, float* &ptrToData) {
        rows = nRows;
        cols = nCols;
        data = ptrToData;
    };

    void print() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {

            }
        }
    };
};

int main() {


    return 0;
}