#ifndef FEATUREEXTRACTION_COMPLEXNUM_H
#define FEATUREEXTRACTION_COMPLEXNUM_H

class Complex
{
public:
	//���캯��
	double real;
	double imag;

	Complex()
	{
		real = 0;
		imag = 0;
	}

	Complex(double a, double b) :real(a), imag(b){}
	
	//��������������
	Complex operator+(Complex &a);
	Complex operator-(Complex &a);
	Complex operator*(Complex &a);
	Complex operator/(Complex &a);
	
	//�����˷�
	Complex power(int n);
};

#endif
