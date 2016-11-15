#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
//Wai Phyo
//Robert Harris
//CS256-HW4
//completed on 02/15/2016

class PolyTester;

class Polynomial
{
    friend class PolyTester;

private:
	double* coeff;
	int size;
public:
	Polynomial();//default constructor
	Polynomial(const double * a, int doSize);//double array to poly
	Polynomial(const Polynomial& other);//copy constructor
	Polynomial(int in);//int to poly
	Polynomial(double in);//double to poly
	Polynomial& operator=(const Polynomial& right);//overload "="
	~Polynomial();//destructor
	int getSize() const;//return size
	int degree() const;//return the degree
	std::string str() const;//convert to string function
	double solve(double x) const;//solving polynomial//actually just substitution
	double& operator[](int index);//overload []
	Polynomial operator+(const Polynomial& right) const;//addition
	Polynomial operator-(const Polynomial& right) const;//subtraction
	Polynomial operator*(const Polynomial& right) const;//multiplication
	Polynomial operator*(const double d) const;//multiplication with constant
	Polynomial operator+=(const Polynomial& right);//add equal
	Polynomial operator-=(const Polynomial& right);//subtract equal
	Polynomial operator*=(const Polynomial& right);//multiplication equal
	bool operator==(const Polynomial& right) const;//test they are the same
	bool operator!=(const Polynomial& right) const;//test they are NOT the same
};
std::ostream& operator<<(std::ostream& os, const Polynomial& s);
#endif
