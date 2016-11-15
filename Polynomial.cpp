//Wai Phyo
//Robert Harris
//CS256-HW4
//completed on 02/15/2016

#include <sstream>
#include <cmath>
#include <cstring>
#include "Polynomial.h"

Polynomial::Polynomial():coeff(new double[1]),size(1)//default constructor
{
	coeff[0]=0;//save it with 0
}
Polynomial::Polynomial(const double * a, int doSize):coeff(new double[doSize]),size(doSize)//double array to poly
{
	for(int i=0;i<doSize;++i)
	{
		coeff[i]=*(a+i);//copy double values to coeficient
	}
}
Polynomial::Polynomial(const Polynomial& other):coeff(new double[other.size]),size(other.size)//copy constructor
{
	for(int i=0;i<size;++i)
	{
		coeff[i]=*(other.coeff+i);//copy double values to coeficient
	}
}
Polynomial::Polynomial(int in):coeff(new double[1]),size(1)//int to poly
{
	coeff[0]=in;//save it with integer
}
Polynomial::Polynomial(double in):coeff(new double[1]),size(1)//double to poly
{
	coeff[0]=in;//save it with integer
}
Polynomial& Polynomial::operator=(const Polynomial& right)//overload "="
{
	if(size < right.size)//if size is smaller, 
	{
		delete[] coeff;//delete existing one
		coeff=new double[right.size];//create new one

	}
	size=right.size;//assign size
	for(int i=0;i<size;++i)//loop and save it to this
	{
		coeff[i]=right.coeff[i];//copy double values to coeficient
	} 
	return * this;//return 
}
Polynomial::~Polynomial()//destructor
{
	delete[] coeff;
	coeff=nullptr;
	size=0;
}
int Polynomial::getSize() const//return size
{
	if(size == 0)//empty polynomial
	{
		return 0;
	}
	for(int a=size-1;a>-1;--a)
	{
		if(coeff[a])
		{
			return (a+1);
		}
	}
	return 0;
}
int Polynomial::degree() const//return the degree
{
	int temp = getSize();//get size
	//adjust since degree is 1 less than size
	temp>0 ? temp = temp-1 : temp = 0;
	return temp;
}
std::string Polynomial::str() const//convert to string function
{
	std::stringstream sout;
	bool first=true;
	if(size <= 0)//if it is empty, return 0
	{
		sout<<"0";
	}
	else
	{
		for(int a= size-1;a>-1;--a)
		{
			if(first)//1st element. no preceding element
			{
				if(coeff[a] > 0)//positive value
				{
					if(coeff[a] >1)//bigger than 1, need to have coefficient
					{
						sout<<coeff[a];
					}
					first=false;//1st time finish
				}
				else if(coeff[a] < 0)//negative value
				{
					sout<<"-";//preceding negative sign

					if(coeff[a] <-1)//less than -1, need to have coefficient
					{
						sout<<(coeff[a]*-1);//already have a negative, remove negative sign
					}
					first=false;//1st time finish
				}
				
			}
			else//not 1st time//need preceding "+" sign
			{
				if(coeff[a] > 0)
				{
					sout<<" + ";
					if(coeff[a] >1)
					{
						sout<<coeff[a];
					}
				}
				else if(coeff[a] < 0)
				{
					sout<<" - ";
					if(coeff[a] <-1)
					{
						sout<<(coeff[a]*-1);
					}
				}
			}
			if(a>1 && coeff[a]!=0)//for "x^ something"
			{
				sout<<"x^"<<(a);//need "to put something
			}
			else if( a==1 && coeff[a]!=0)//just need x
			{
				sout<<"x";
			}
		}
	}
	if(sout.str() == "")
	{	
		sout<<"0";
	}
	return sout.str();
}
double Polynomial::solve(double x) const//solving polynomial//actually just substitution
{
	double result=0;//declare result
	for(int a=0;a<size;++a)//loop and add
	{
		result += coeff[a] * pow(x, (double)a);//get power for each
	}
	return result;//return result
}
double& Polynomial::operator[](int index)//overload []
{
	if(index < 0)//validation
	{
		std::cout<<"ERROR: array out of bounds. returning invalid position. DO NOT USE THIS"<<std::endl;
	}
	if(index >= size)//bigger than we have
	{
		double* temp=new double[index+1];//create new temp array
		for(int a=0;a<index+1;++a)//copy existing items to new array
		{
			(a < size) ? temp[a]=coeff[a] : temp[a]=0;//fill the temp array
		}
		size=index+1;//update size
		delete[] coeff;//remove existing array
		coeff=temp;//point to new array
	}
	return *(coeff+index);//return the index
}
Polynomial Polynomial::operator+(const Polynomial&right) const//addition
{
	int newSize=0;//declare new size
	(size < right.size) ? newSize=right.size : newSize=size;//calculate new size
	double * temp = new double[newSize];//declare temp arrray
	for(int a=0;a<newSize;++a)//calculate for temp array
	{
		(a < size) ? temp[a]=coeff[a] : temp[a]=0;//fill the temp array
		if( a < right.size)//get right size and add them
		{
			temp[a]=temp[a] + right.coeff[a];
		}
	}
	Polynomial tempPoly(temp,newSize);//create new Polynomial instance
	delete[] temp;//remove temp
	return tempPoly;//return new instance
}
Polynomial Polynomial::operator-(const Polynomial&right) const//substraction
{
	Polynomial tempPoly = *this + (right * -1);//multiply with negative constant and add them
	return tempPoly;
}
Polynomial Polynomial::operator*(const Polynomial&right) const//multiplication
{
	int newSize=size + right.size - 1;	//create new size for result
	double * temp = new double[newSize];//create temp array
	for(int a=0;a<newSize;++a)//fill with values 1st level multiplication
	{
		(a < size) ? temp[a]=coeff[a]*right.coeff[0] : temp[a]=0;
	}
	for(int a=1;a<right.size;++a)//loop and multiply the rest. FOILing
	{
		for(int b=0;b<size;++b)
		{
			temp[a+b] = temp[a +b] + (coeff[b]*right.coeff[a]);
		}
	}
	Polynomial tempPoly(temp,newSize);//create new Polynomial 
	delete[] temp;
	return tempPoly;
}
Polynomial Polynomial::operator*(const double d) const//multiplication
{	
	double * temp = new double[size];
	for(int a=0;a<size;++a)//loop and multiply with constant
	{
		temp[a] = coeff[a] * d;
	}
	Polynomial tempPoly(temp,size);
	delete[] temp;
	return tempPoly;
}
Polynomial Polynomial::operator+=(const Polynomial& right)//substraction
{
	Polynomial temp=*this + right;//perform operation and save to temp polynomial
	*this = temp;//update polynomial
	return *this;
}
Polynomial Polynomial::operator-=(const Polynomial& right)//multiplication
{
	Polynomial temp=*this + (right * -1);//perform operation and save to temp polynomial
	*this = temp;//update polynomial
	return *this;
}
Polynomial Polynomial::operator*=(const Polynomial& right)//multiplication
{
	Polynomial temp=*this * right;//perform operation and save to temp polynomial
	*this = temp;//update polynomial
	return *this;
}
bool Polynomial::operator==(const Polynomial& right) const//test they are the same
{
	if(size != right.size)//size not equal. no way they are equal
	{
		return false;
	}
	for(int a=0;a<size;++a)//check item by item
	{
		if(coeff[a] != right.coeff[a])//one of them is not equal, they are not
		{
			return false;
		}
	}
	return true;
}
bool Polynomial::operator!=(const Polynomial& right) const//test they are NOT the same
{
	return ! (*this == right);//opposite of "=="
}
std::ostream& operator<<(std::ostream& os, const Polynomial& s)
{
	os<<s.str();//return string
	return os;
}
