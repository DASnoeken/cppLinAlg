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
        std::cout << m->returnElement(0, 0) << "  " << m->returnElement(0, 1) << "  " << m->returnElement(1,2) << std::endl;
        m->setElement(1, 1, 23.0);
    }
    catch (MatrixException me) {
        std::cout << "\033[1;31mERROR!\033[0m " << "Exception caught!" << std::endl;
    }
}