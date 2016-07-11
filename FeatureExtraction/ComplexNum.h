#ifndef FEATUREEXTRACTION_COMPLEXNUM_H
#define FEATUREEXTRACTION_COMPLEXNUM_H

class Complex
{
public:
	//构造函数
	double real;
	double imag;

	Complex()
	{
		real = 0;
		imag = 0;
	}

	Complex(double a, double b) :real(a), imag(b){}
	
	//复数的四则运算
	Complex operator+(Complex &a);
	Complex operator-(Complex &a);
	Complex operator*(Complex &a);
	Complex operator/(Complex &a);
	
	//复数乘方
	Complex power(int n);
};

#endif
