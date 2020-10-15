#include "Matrix.h"
#include "MatrixException.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <string_view>
#include <charconv>
#include <memory>

Matrix::Matrix(const char* input)
{

	int* dim = inputToDim(input);
	this->n_rows = dim[0];
	this->n_columns = dim[1];
	this->rows.reserve(this->n_rows);
	std::vector<double> row;
	row.reserve(this->n_columns);
	this->rrMult = 1.0;
	std::string_view delimiter = ",";
	std::string_view delimiter2 = ";";
	std::string_view sv(input);
	double d;
	for (int j = 0; j < n_rows; j++) {
		for (int i = 0; i < n_columns; i++) {
			//std::cout << "sv: " << sv << " delims: " << sv.find(delimiter) << " " << sv.find(delimiter2) << std::endl;
			if (sv.find(delimiter2) == std::string_view::npos) {
				if (sv.find(delimiter) != std::string_view::npos)
					std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter), d);		//sv.substr(0,sv.find(delimiter))
				else
					std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.size(), d);
				sv = std::string_view(sv.data() + sv.find(delimiter) + 1);// .erase(0, sv.find(delimiter) + 1);
				row.emplace_back(d);
			}
			else {
				if (sv.find(delimiter) < sv.find(delimiter2)) {
					if (sv.find(delimiter) != std::string_view::npos) {
						std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter), d);
					}
					sv = std::string_view(sv.data() + sv.find(delimiter) + 1);
					row.emplace_back(d);
				}
				else {
					if (sv.find(delimiter2) != std::string_view::npos) {
						std::from_chars_result val = std::from_chars(sv.data(), sv.data() + sv.find(delimiter2), d);
					}
					sv = std::string_view(sv.data() + sv.find(delimiter2) + 1);
					row.emplace_back(d);
				}
			}
		}
		this->rows.emplace_back(row);
		row.clear();
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
			row.emplace_back(0.0);
		}
		this->rows.emplace_back(row);
	}
}

Matrix::Matrix(const Matrix& m_old)	//copy ctor
{
	this->n_rows = m_old.getN_rows();
	this->n_columns = m_old.getN_columns();
	this->rrMult = 1.0;
	this->rows.reserve(this->n_rows);
	std::vector<double> row;
	row.reserve(this->n_columns);
	for (int i = 0; i < this->n_rows; i++) {
		for (int j = 0; j < this->n_columns; j++) {
			row.emplace_back(m_old.getElement(i,j));
		}
		this->rows.emplace_back(row);
		row.clear();
	}
}

void Matrix::printElements() {
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->n_columns; j++) {
			std::cout << std::left << std::setw(4) << this->rows.at(i).at(j) << " ";
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
	this->rows.at(i).at(j) = val;
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

const Matrix Matrix::operator+(const Matrix& m)
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

const Matrix Matrix::operator-(const Matrix& m)
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

const Matrix Matrix::operator*(const Matrix& m)
{
	if (this->getN_columns() != m.getN_rows()) {
		MatrixException me("Inner dimension mismatch!");
		std::cout << me.toString() << " " << me.getWhat() << " at Matrix::multiply(" << &m << ")" << std::endl;
		throw me;
	}
	Matrix mAns(this->getN_rows(), m.getN_columns());
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

const Matrix Matrix::operator*(const double& scalar)
{
	Matrix m(this->getN_rows(), this->getN_columns());
	for (int i = 0; i < this->getN_rows(); i++) {
		for (int j = 0; j < this->getN_columns(); j++) {
			m.setElement(i, j, scalar * this->getElement(i, j));
		}
	}
	return m;
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
	int out[2];
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
	return this->rows.at(i).at(j);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	for (int i = 0; i < m.getN_rows(); i++) {
		for (int j = 0; j < m.n_columns; j++) {
			os << std::left << std::setw(4) << m.rows.at(i).at(j) << " ";
		}
		os << "\n";
	}
	os << std::endl;
	return os;
}
