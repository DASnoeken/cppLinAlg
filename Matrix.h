#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
	Matrix(std::string input);
	~Matrix();
	int* inputToDim(std::string in);
	double returnElement(int i, int j);
	void printElements();
	void setElement(int i, int j, double val);
private:
	int n_rows, n_columns;
	//double **rows;
	std::vector< std::vector<double> > rows;
};

