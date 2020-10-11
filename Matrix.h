#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
	Matrix(std::string input);
	Matrix(int i, int j);
	~Matrix();
	int* inputToDim(std::string in);
	const double returnElement(int i, int j) const;
	void printElements();
	void setElement(int i, int j, double val);
	Matrix multiply(const Matrix& m);

	const int getN_rows() const;
	const int getN_columns() const;
private:
	int n_rows, n_columns;
	std::vector< std::vector<double> > rows;
};

