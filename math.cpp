#include <iostream>
#include "Matrix.h"
#include <memory>
#include "MatrixException.h"


int main()
{
    std::string input = "1,2,3;4,5,6;7,8,9";
    std::unique_ptr<Matrix> m = std::make_unique<Matrix>(input);
    m->printElements();
    try {
        std::cout << m->returnElement(0, 0) << "  " << m->returnElement(0, 1) << "  " << m->returnElement(2,1) << std::endl;
    }
    catch (MatrixException me) {
        std::cout << "Exception caught!" << std::endl;
    }
}