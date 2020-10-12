#include "Matrix.h"
#include "MatrixException.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <string_view>
#include <charconv>

Matrix::Matrix(const char* input)
{
	int* dim = inputToDim(input);
	this->n_rows = dim[0];
	this->n_columns = dim[1];
	this->rrMult = 1.0;
	std::vector<double> row;
	std::string delimiter = ",";
	std::string delimiter2 = ";";
	std::string_view sv(input);
	for (int j = 0; j < n_rows; j++) {
		for (int i = 0; i < n_columns; i++) {
			//std::cout << "sv: " << sv << " delims: " << sv.find(delimiter) << " " << sv.find(delimiter2) << std::endl;
			if (sv.find(delimiter2) == std::string_view::npos) {
				double d;
				if (sv.find(delimiter) != std::string_view::npos)
					std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter), d);		//sv.substr(0,sv.find(delimiter))
				else
					std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.size(), d);
				sv = std::string_view(sv.data() + sv.find(delimiter) + 1);// .erase(0, sv.find(delimiter) + 1);
				row.push_back(d);
			}
			else {
				if (sv.find(delimiter) < sv.find(delimiter2)) {
					double d;
					if (sv.find(delimiter) != std::string_view::npos) {
						std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter), d);
					}
					sv = std::string_view(sv.data() + sv.find(delimiter) + 1);
					row.push_back(d);
				}
				else {
					double d;
					if (sv.find(delimiter2) != std::string_view::npos) {
						std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter2), d);
					}
					sv = std::string_view(sv.data() + sv.find(delimiter2) + 1);
					row.push_back(d);
				}
			}
		}
		this->rows.push_back(row);
	}
}

Matrix::Matrix(int i, int j)
{
	this->n_rows = i;
	this->n_columns = j;
	this->rrMult = 1.0;
	std::vector<double> row;
	for (int i = 0; i < this->n_rows; i++) {
		for (int j = 0; j < this->n_columns; j++) {
			row.push_back(0.0);
		}
		this->rows.push_back(row);
	}
}

Matrix::Matrix(const Matrix& m_old)	//copy ctor
{
	this->n_rows = m_old.getN_rows();
	this->n_columns = m_old.getN_columns();
	this->rrMult = 1.0;
	std::vector<double> row;
	for (int i = 0; i < this->n_rows; i++) {
		for (int j = 0; j < this->n_columns; j++) {
			row.push_back(m_old.getElement(i,j));
		}
		this->rows.push_back(row);
	}
}

void Matrix::printElements() {
	std::vector<double> vd = this->rows.at(this->getN_rows()-1);
	std::vector<double>::iterator iter = vd.begin();
	while (iter != vd.end()) {
		for (int j = 0; j < this->n_columns; j++) {
			std::cout << std::left << std::setw(4) << *iter << " ";
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
	this->rows.at(this->n_rows - 1).at(j + i * this->n_columns) = val;
}

const Matrix Matrix::multiply(const Matrix& m)
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
				value += this->getElement(i, k) * m.getElement(k, j);
			}
			mAns.setElement(i, j, value);
			value = 0.0;
		}
	}
	return mAns;
}

const Matrix Matrix::add(const Matrix& m)
{
	if (this->getN_rows() != m.getN_rows() || this->getN_columns() != m.getN_columns()) {
		MatrixException me("Dimension mismatch!");
		std::cout << me.toString() << " " << me.getWhat() << " at Matrix::add(" << &m << ")" << std::endl;
		throw me;
	}
	Matrix mAns(this->getN_rows(), this->getN_columns());
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->getN_columns(); j++) {
			mAns.setElement(i, j, this->getElement(i, j) + m.getElement(i, j));
		}
	}
	return mAns;
}

const Matrix Matrix::subtract(const Matrix& m)
{
	if (this->getN_rows() != m.getN_rows() || this->getN_columns() != m.getN_columns()) {
		MatrixException me("Dimension mismatch!");
		std::cout << me.toString() << " " << me.getWhat() << " at Matrix::subtract(" << &m << ")" << std::endl;
		throw me;
	}
	Matrix mAns(this->getN_rows(), this->getN_columns());
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->getN_columns(); j++) {
			mAns.setElement(i, j, this->getElement(i, j) - m.getElement(i, j));
		}
	}
	return mAns;
}

const Matrix Matrix::transpose()
{
	Matrix mAns(this->getN_rows(), this->getN_columns());
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->getN_columns(); j++) {
			mAns.setElement(i, j, this->getElement(j, i));
		}
	}
	return mAns;
}

const Matrix Matrix::scalar(const double& scalar)
{
	Matrix m(this->getN_rows(), this->getN_columns());
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->getN_columns(); j++) {
			m.setElement(i, j, scalar * this->getElement(i, j));
		}
	}
	return m;
}

const Matrix Matrix::REF()
{
	Matrix m(*this);
	for (int i = 0; i < m.getN_rows(); i++) {
		double diagVal = m.getElement(i, i);
		for (int j = i+1; j < m.getN_rows(); j++) {
			double currentElement = m.getElement(j, i);
			double mult = currentElement / diagVal;
			for (int c = 0; c < m.getN_columns(); c++) {
				m.setElement(j, c, m.getElement(j, c) - mult * m.getElement(i, c));
			}
		}
	}
	return m;
}

const double Matrix::det()
{
	if (this->getN_rows() != this->getN_columns()) {
		MatrixException me("Matrix needs to be square!");
		std::cout << me.toString() << " " << me.getWhat() << " " << " at Matrix::det()" << std::endl;
		throw me;
	}
	double diagProd = 1.0;
	Matrix m = this->REF();
	for (int i = 0; i < this->getN_rows(); i++) {
		diagProd *= m.getElement(i, i);
	}
	return m.getRrMult() * diagProd;
}

const int Matrix::getN_rows() const
{
	return n_rows;
}

const int Matrix::getN_columns() const
{
	return this->n_columns;
}

const double Matrix::getRrMult() const
{
	return this->rrMult;
}

Matrix::~Matrix()
{
	
}

int* Matrix::inputToDim(std::string_view in)
{
		static int out[2];
		int nrows = 1;
		int ncol = 1;
		int colcount = 0;
		bool cols = true;
		for (int i = 0; i < in.size(); i++) {
			if (in.data()[i] == ';') {
				nrows++;
			}
			else if (in.data()[i] == ',') {
				colcount++;
			}
			if (cols && (in.data()[i] == ';' || i== in.size()-1)) {
				ncol += colcount;
				cols = false;
			}
		}
		out[0] = nrows;
		out[1] = ncol;
		return out;
	
}

const double Matrix::getElement(int i, int j) const
{
	if (i >= this->n_rows || j >= this->n_columns) {
		MatrixException me("Index out of bounds!");
		std::cout << me.toString() << "  " << me.getWhat() << " at Matrix::getElement(" << i << ", " << j << ")" << std::endl;
		throw me;
	}
	std::vector<double> vd = this->rows.at(this->n_rows - 1);
	std::vector<double>::iterator iter = vd.begin();
	iter += j+i*this->n_columns;
	return *iter;
}
