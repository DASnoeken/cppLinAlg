#include <iostream>
#include "Matrix.h"
#include <memory>
#include "MatrixException.h"
#include "BigInt.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
#include <array>

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
        std::cout << "Addition: \n";
        Matrix m4 = m + m2;
        m4.printElements();
        
        std::cout << "multiply: \n";
        Matrix m3 = m*m2;
        m3.printElements();
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
    const char* biIn = "123456789987654321123456789987654321";
    BigInt bi(biIn);
    bi.printNumber();
    BigInt b = bi + bi;
    std::cout << " + ";
    bi.printNumber();
    std::cout << " = ";
    b.printNumber();
    std::cout << std::endl;
}


//Here is some stuff to find memory leaks

/*int const MY_SIZE = 25;
int alloc = 0;
int dealloc = 0;
std::array<void*, MY_SIZE> myAlloc{ nullptr, };

void* operator new(size_t sz) {
    static int counter{};
    void* ptr = malloc(sz);
    myAlloc.at(counter++) = ptr;
    std::cout << "Addr.: " << ptr << " size: " << sz << std::endl;
    alloc++;
    return ptr;
}

void operator delete(void* ptr) noexcept {
    auto ind = std::distance(myAlloc.begin(), std::find(myAlloc.begin(), myAlloc.end(), ptr));
    myAlloc[ind] = nullptr;
    dealloc++;
    free(ptr);
}

void operator delete[](void* ptr, std::size_t sz){
    dealloc++;
    delete (ptr); // ::operator delete(ptr) can also be used
}

void getInfo() {

    std::cout << std::endl;

    std::cout << "Not deallocated: " << std::endl;
    for (auto i : myAlloc) {
        if (i != nullptr) std::cout << " " << i << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Allocations: " << alloc << " -- Deallocations: " << dealloc << " -- Difference: " << alloc - dealloc << std::endl;
}*/