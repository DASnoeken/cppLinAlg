#pragma once
#include <iostream>
#include <vector>
#include <string_view>
class Matrix
{
public:
	Matrix(const char* input);
	Matrix(int i, int j);
	Matrix(const Matrix& m_old);
	~Matrix();
	int* inputToDim(std::string_view in);
	const double getElement(int i, int j) const;
	void printElements();
	void setElement(int i, int j, double val);
	const Matrix multiply(const Matrix& m);
	const Matrix add(const Matrix& m);
	const Matrix subtract(const Matrix& m);
	const Matrix transpose();
	const Matrix scalar(const double& scalar);
	const Matrix REF();
	const double det();

	const int getN_rows() const;
	const int getN_columns() const;
	const double getRrMult() const;
private:
	int n_rows, n_columns;
	std::vector< std::vector<double> > rows;
	double rrMult;
};

