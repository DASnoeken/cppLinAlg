#include <iostream>
#include "Matrix.h"
#include <memory>
#include "MatrixException.h"

int* inputToDim(std::string in);

int main()
{
    std::string input = "1,2,3;4,5,6;7,8,9";
    int* dim = inputToDim(input);
    std::cout << "size found: " << dim[0] << " x " << dim[1] << std::endl;
    std::unique_ptr<Matrix> m = std::make_unique<Matrix>(dim[0],dim[1],input);
    m->printElements();
    try {
        std::cout << m->returnElement(0, 0) << "  " << m->returnElement(0, 1) << "  " << m->returnElement(1, 1) << std::endl;
    }
    catch (MatrixException me) {
        std::cout << "Exception caught!" << std::endl;
    }
}

int* inputToDim(std::string in) {
    static int out[2];
    int nrows = 1;
    int ncol = 1;
    int colcount = 0;
    bool cols = true;
    for (int i = 0; i < in.size(); i++) {
        if (in.at(i) == ';') {
            nrows++;
            if (cols) {
                ncol += colcount;
            }
            cols = false;
        }
        else if (in.at(i) == ',') {
            colcount++;
        }
    }
    out[0] = nrows;
    out[1] = ncol;
    return out;
}