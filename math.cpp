#include <iostream>
#include "Matrix.h"
#include <memory>
#include "MatrixException.h"
#include "BigInt.h"


int main()
{
    const char* input = "1,2,3;4,5,6;7,8,93";
    Matrix m(input);
    const char* input2 = "1,1,1;2,2,2;3,3,3";
    Matrix m2(input2);
    m.printElements();
    m2.printElements();
    try {
        std::cout << "Test getElement: " << m.getElement(0, 0) << "  " << m.getElement(0, 1) << "  " << m.getElement(1,2) << std::endl;
        std::cout << "multiply: \n";
        Matrix m3 = m*m2;
        m3.printElements();
        std::cout << "Addition: \n";
        Matrix m4 = m+m2;
        m4.printElements();
        std::cout << "Subtraction: \n";
        Matrix m5 = m-m2;
        m5.printElements();
        std::cout << "Transpose: \n";
        Matrix m6 = m.transpose();
        m6.printElements();
        std::cout << "Scalar: \n";
        Matrix m7 = m*2;
        m7.printElements();
        Matrix m8 = m.REF();
        Matrix m9("1,3,2;4,3,6;33,21,17");
        m9.printElements();
        m9 = m9.REF();
        m9.printElements();
        Matrix m10("2,3,5;7,11,13;17,19,23");
        double m10determinant = m10.det();
        std::cout << "determinant of: \n";
        m10.printElements();
        std::cout << " = " << m10determinant << std::endl;
    }
    catch (MatrixException me) {
        std::cout << "\033[1;31mERROR!\033[0m " << "Exception caught!" << std::endl;
    }
    const char* biIn = "123456789987654321123456789";
    BigInt bi(biIn);
    bi.printNumber();
}