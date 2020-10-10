#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
	Matrix(int n, int m, std::string input);
	~Matrix();
	double returnElement(int i, int j);
	void printElements();
private:
	int n_rows, n_columns;
	//double **rows;
	std::vector< std::vector<double> > rows;
};

