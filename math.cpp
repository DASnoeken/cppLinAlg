#include <iostream>
#include "Matrix.h"
#include "MatrixException.h"
#include "BigIntException.h"
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
        std::cout << me << "Exception caught!" << std::endl;
    }
    try {
        std::cout << "Test BigInt class" << std::endl;
        const char* biIn = "7894561315345548498498615615164897894841321312565498789784655465135111303110123151301051354848948351132135157984561231";
        BigInt bi(biIn);
        bi.printNumber();
        int i = 31231;
        BigInt bi2 = bi + i;
        bi2.printNumber();
        bi.get_INT_MAX().printNumber();


        std::cout << "\n\nTesting operator*" << std::endl;
        BigInt bis("12");
        BigInt bis2("11");
        BigInt bisans = bis * bis2;
        bisans.printNumber();
        

        std::cout << "\n\nTesting operator^" << std::endl;
        BigInt bip("3");
        BigInt bip2("4");
        BigInt bipans = (bip ^ bip2);
        std::cout << (3 * 3 * 3 * 3) << " = " << bipans << std::endl;
        std::cout << "Some BigInt: " << BigInt("319208385719841092417498324") << std::endl;
        long long lb = bipans.to_LLONG();
        std::cout << bipans << " = " << lb << std::endl;

        std::cout << "\n\nTesting operator-" << std::endl;
        BigInt test = BigInt(123) - BigInt(25);
        std::cout << "123 - 25 = " << test << std::endl;
        BigInt test2 = BigInt("9999999999999999999999999999999999999999") - BigInt("3211233213561234821342511");
        std::cout << "9999999999999999999999999999999999999999 - 3211233213561234821342511 = " << test2 << std::endl;
        BigInt test3 = BigInt("123123123123123123123123123123123123123123123123") - BigInt("246246246246246246");
        std::cout << "123123123123123123123123123123123123123123123123 - 246246246246246246 = " << test3 << std::endl;
        
        std::cout << "\n\nTesting operator/" << std::endl;
        BigInt bid(13);
        BigInt bid2(3);
        BigInt bidans = bid / bid2;
        
        std::cout << "Actual 13/3 = " << 13 / 3 << std::endl;
        std::cout << bid << "/" << bid2 << " = " << bidans << std::endl;

        BigInt bidans2 = BigInt(12) / BigInt(13);
        std::cout << "Actual 12/13 = " << 12 / 13 << std::endl;
        std::cout << "12/13 = " << bidans2 << std::endl;
        std::cout << "\nOther bases test" << std::endl;

        BigInt bibase16("1234ABCDEF313", (short)16);
        std::cout << "bibase16 = " << bibase16 << std::endl;
        BigInt bibase16sum = (bibase16 + bibase16);
        bibase16sum.printDigits();
        std::cout << bibase16sum << std::endl;
        
        std::cout << "\nTesting factorial" << std::endl;
        BigInt biFactorial = BigInt::factorial(BigInt(10));
        std::cout << "10! = " << biFactorial << std::endl;
        std::cout << "12! = " << BigInt::factorial(12) << std::endl;
        std::cout << "20! = " << BigInt::factorial(20) << std::endl;
        std::cout << "100! = " << BigInt::factorial(100) << std::endl;
    }
    catch (BigIntException& bie) {
        std::cout << "\033[1;31mError!" << " " << bie.getWhat() << "\033[0m" << std::endl;
    }
}

//Here is some stuff to find memory leaks

/*#include <algorithm>
#include <cstdlib>
#include <new>
#include <string>
#include <array>


int const MY_SIZE = 25;
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

void operator delete[](void* ptr, std::size_t sz) {
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