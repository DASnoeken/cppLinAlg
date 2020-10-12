#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
	Matrix(std::string input);
	Matrix(int i, int j);
	Matrix(const Matrix& m_old);
	~Matrix();
	int* inputToDim(std::string in);
	const double getElement(int i, int j) const;
	void printElements();
	void setElement(int i, int j, double val);
	const Matrix multiply(const Matrix& m);
	const Matrix add(const Matrix& m);
	const Matrix subtract(const Matrix& m);
	const Matrix transpose();
	const Matrix scalar(const double& scalar);
	const Matrix REF();

	const int getN_rows() const;
	const int getN_columns() const;
private:
	int n_rows, n_columns;
	std::vector< std::vector<double> > rows;
};

