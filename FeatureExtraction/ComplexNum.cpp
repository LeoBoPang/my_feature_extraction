#include "ComplexNum.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

//Overload "+"
Complex Complex::operator+(Complex &a)
{
	Complex temp;
	temp.real = real + a.real;
	temp.imag = imag + a.imag;
	return temp;
}

////Overload "-"
Complex Complex::operator-(Complex &a)
{
	Complex temp;
	temp.real = real - a.real;
	temp.imag = imag - a.imag;
	return temp;
}

//Overload "*"
Complex Complex::operator*(Complex &a)
{
	Complex temp;
	temp.real = real*a.real - imag*a.imag;
	temp.imag = real*a.imag + a.real*imag;
	return temp;
}

//Overload " / "
Complex Complex::operator/(Complex &a)
{
	Complex temp;
	if (a.real != 0 && a.imag != 0)
	{
		cout << "error!" << endl;
	}
	else
	{
		temp.real = (real*a.real - imag*(-a.imag)) / (a.real*a.real + a.imag*imag);
		temp.imag = (real*(-a.imag) + a.real*imag) / (a.real*a.real + a.imag*imag);
	}
	return temp;
}

//Overload " power "
Complex Complex::power(int n)
{
	Complex temp;
	temp = *this;
	for (int i = 1; i<n; i++)
	{
		temp = (*this)*temp;
	}
	return temp;
}