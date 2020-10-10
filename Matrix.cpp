#include "Matrix.h"
#include "MatrixException.h"
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>

Matrix::Matrix(int n, int m, std::string input)
{
	this->n_rows = n;
	this->n_columns = m;
	std::vector<double> row;
	std::string delimiter = ",";
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if(input.find(delimiter)<input.find(";")){
				double val = std::stod(input.substr(0,input.find(delimiter)));
				input.erase(0, input.find(delimiter) + 1);
				row.push_back(val);
			}
			else {
				double val = std::stod(input.substr(0, input.find(";")));
				input.erase(0, input.find(";") + 1);
				row.push_back(val);
			}
		}
		this->rows.push_back(row);
	}
}

void Matrix::printElements() {
	std::vector<double> vd = this->rows.at(this->n_rows-1);
	std::vector<double>::iterator iter = vd.begin();
	while (iter != vd.end()) {
		for (int j = 0; j < this->n_columns; j++) {
			std::cout << *iter << " ";
			++iter;
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

Matrix::~Matrix()
{
	
}

double Matrix::returnElement(int i, int j)
{
	if (i >= this->n_rows || j >= this->n_columns) {
		MatrixException me("Index out of bounds!");
		std::cout << me.toString() << "  " << me.getWhat() << " at Matrix::returnElement(int i, int j)" << std::endl;
		throw me;
	}
	std::vector<double> vd = this->rows.at(this->n_rows - 1);
	std::vector<double>::iterator iter = vd.begin();
	iter += j+i*this->n_columns;
	return *iter;
}
