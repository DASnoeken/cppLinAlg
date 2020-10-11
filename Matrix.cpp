#include "Matrix.h"
#include "MatrixException.h"
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>

Matrix::Matrix(std::string input)
{
	int* dim = inputToDim(input);
	this->n_rows = dim[0];
	this->n_columns = dim[1];
	std::vector<double> row;
	std::string delimiter = ",";
	for (int j = 0; j < n_rows; j++) {
		for (int i = 0; i < n_columns; i++) {
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

Matrix::Matrix(int i, int j)
{
	this->n_rows = i;
	this->n_columns = j;
	std::vector<double> row;
	for (int j = 0; j < n_rows; j++) {
		for (int i = 0; i < n_columns; i++) {
			row.push_back(0.0);
		}
		this->rows.push_back(row);
	}
}

void Matrix::printElements() {
	std::vector<double> vd = this->rows.at(this->getN_rows()-1);
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

void Matrix::setElement(int i, int j, double val)
{
	if (i >= this->n_rows || j >= this->n_columns) {
		MatrixException me("Index out of bounds!");
		std::cout << me.toString() << "  " << me.getWhat() << " at Matrix::setElement(" << i << ", " << j << ", " << val << ")" << std::endl;
		throw me;
	}
	//std::cout << "Before: " << std::endl;
	//this->printElements();
	this->rows.at(this->n_rows - 1).at(j + i * this->n_columns) = val;
	//std::cout << "After: " << std::endl;
	//this->printElements();
}

Matrix Matrix::multiply(const Matrix& m)
{
	if (this->getN_columns() != m.getN_rows()) {
		MatrixException me("Inner dimension mismatch!");
		std::cout << me.toString() << " " << me.getWhat() << " at Matrix::multiply(" << &m << ")" << std::endl;
		throw me;
	}
	Matrix mAns(this->getN_rows(),m.getN_columns());
	double value = 0.0;
	for (int i = 0; i < mAns.getN_rows(); i++) {
		for (int j = 0; j < mAns.getN_columns(); j++) {
			for (int k = 0; k < this->getN_columns(); k++) {
				value += this->returnElement(i, k) * m.returnElement(k, j);
			}
			mAns.setElement(i, j, value);
			value = 0.0;
		}
	}
	std::cout << "rows: " << mAns.getN_rows() << " columns: " << mAns.getN_columns() << std::endl;
	return mAns;
}

const int Matrix::getN_rows() const
{
	return n_rows;
}

const int Matrix::getN_columns() const
{
	return this->n_columns;
}

Matrix::~Matrix()
{
	
}

int* Matrix::inputToDim(std::string in)
{
		static int out[2];
		int nrows = 1;
		int ncol = 1;
		int colcount = 0;
		bool cols = true;
		for (int i = 0; i < in.size(); i++) {
			if (in.at(i) == ';') {
				nrows++;
				if (cols) {
					ncol += colcount;
				}
				cols = false;
			}
			else if (in.at(i) == ',') {
				colcount++;
			}
		}
		out[0] = nrows;
		out[1] = ncol;
		return out;
	
}

const double Matrix::returnElement(int i, int j) const
{
	if (i >= this->n_rows || j >= this->n_columns) {
		MatrixException me("Index out of bounds!");
		std::cout << me.toString() << "  " << me.getWhat() << " at Matrix::returnElement(" << i << ", " << j << ")" << std::endl;
		throw me;
	}
	std::vector<double> vd = this->rows.at(this->n_rows - 1);
	std::vector<double>::iterator iter = vd.begin();
	iter += j+i*this->n_columns;
	return *iter;
}
