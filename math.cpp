#include <iostream>
#include "Matrix.h"
#include <memory>
#include "MatrixException.h"


int main()
{
    std::string input = "1,2,3;4,5,6;7,8,9";
    std::unique_ptr<Matrix> m = std::make_unique<Matrix>(input);
    std::string input2 = "1,1,1;2,2,2;3,3,3";
    Matrix m2(input2);
    m->printElements();
    m2.printElements();
    try {
        std::cout << m->returnElement(0, 0) << "  " << m->returnElement(0, 1) << "  " << m->returnElement(1,2) << std::endl;
        //m->setElement(1, 1, 23.0);
        std::cout << "multiply: \n";
        Matrix m3 = m->multiply(m2);
        m3.printElements();
        std::cout << "Addition: \n";
        Matrix m4 = m->add(m2);
        m4.printElements();
        std::cout << "Subtraction: \n";
        Matrix m5 = m->subtract(m2);
        m5.printElements();
        std::cout << "Transpose: \n";
        Matrix m6 = m->transpose();
        m6.printElements();
    }
    catch (MatrixException me) {
        std::cout << "\033[1;31mERROR!\033[0m " << "Exception caught!" << std::endl;
    }
}