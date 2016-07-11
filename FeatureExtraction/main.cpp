#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "ComplexNum.h"
#include "bessj1.h"
#include "Preparation.h"
using namespace std;

const int pixel = 64;
const int k = 1;
const int N = 20;
const int M = 20;

void main()
{
	extern void readImage(int);
	extern double bessj1(double);
	extern int* readImgData(int);
	extern double* readZn();
	extern double* readAn();

	long double s = 4 / double (pixel) / double (pixel) / k / k;

	readImage(pixel);
	int *imgData = readImgData(pixel);
	double *An = readAn();
	double *Zn = readZn();


	//Compute the sin and cos value according to location (x,y) for each k point and the distance to the center point.
	double x = 0, y = 0;
	double *cosK = new double[pixel * pixel * k * k];
	double *sinK = new double[pixel * pixel * k * k];
	double *rK = new double[pixel * pixel * k * k];

	for (int pixelRow = 0; pixelRow < pixel; pixelRow++){
		for (int pixelCol = 0; pixelCol < pixel; pixelCol++){
			for (int kRow = 0; kRow < k; kRow++){
				for (int kCol = 0; kCol < k; kCol++){
					x = -1 + (2 / pixel) * pixelCol + (1 / pixel / k) * (2 * kCol + 1);
					y = 1 - (2 / pixel) * pixelRow - (1 / pixel / k) * (2 * kRow + 1);
					rK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol] = sqrt(x * x + y * y);
					cosK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol] = x / rK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol];
					sinK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol] = y / rK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol];
					if (rK[pixelRow * pixel * k * k + pixelCol * k * k + kRow * k + kCol]> 1){
						imgData[pixelRow * pixel + pixelCol] = -1;
					}
				}
			}
		}
	}


	//Compute the image feature based on Bessel-Fourier moments
	Complex MMoment[N* (M * 2 + 1)];
	Complex momentTemp;
	Complex momentKPoint;
	Complex momentPixel;

	double bessValue;
	for (int n = 1; n <= N; n++){
		for (int m = 0; m < 2 * M + 1; m++){
			for (int pixelIndex = 0; pixelIndex < pixel * pixel; pixelIndex++){
				if (imgData[pixelIndex] < 0){
					continue;
				}
				for (int kIndex = 0; kIndex < k * k; kIndex++){
					
					bessValue = bessj1(rK[pixelIndex * k * k + kIndex] * Zn[n - 1]);

					if (m < (M)){
						momentTemp.real = cosK[pixelIndex * k * k + kIndex];
						momentTemp.imag = sinK[pixelIndex * k * k + kIndex];
						momentTemp = momentTemp.power(M - m);
						momentTemp.real = momentTemp.real * bessValue;
						momentTemp.imag = momentTemp.imag * bessValue;
						momentKPoint = momentKPoint + momentTemp;
					}

					else if (m > (M)){
						momentTemp.real = cosK[pixelIndex * k * k + kIndex];
						momentTemp.imag = -sinK[pixelIndex * k * k + kIndex];
						momentTemp = momentTemp.power(m - M);
						momentTemp.real = momentTemp.real * bessValue;
						momentTemp.imag = momentTemp.imag * bessValue;
						momentKPoint = momentKPoint + momentTemp;
					}

					else if (m == M){
						momentKPoint.real = momentKPoint.real + bessValue;
					}
				}   //Here is the end for K loop
				momentKPoint.real = momentKPoint.real * imgData[pixelIndex];
				momentKPoint.imag = momentKPoint.imag * imgData[pixelIndex];
				momentPixel = momentPixel + momentKPoint;
				momentKPoint.real = 0;
				momentKPoint.imag = 0;
			}   //Here is the end for Pixel loop
			momentPixel.real = momentPixel.real * s * An[n - 1];
			momentPixel.imag = momentPixel.imag * s * An[n - 1];
			MMoment[(n - 1) * (2 * M + 1) + m] = momentPixel;
			momentPixel.real = 0;
			momentPixel.imag = 0;
		}  // end of M loop
	}  // end of N loop


	delete[] An;
	delete[] cosK;
	delete[] sinK;
	delete[] rK;


	double *cosKRec = new double[pixel * pixel];
	double *sinKRec = new double[pixel * pixel];
	double *rKRec = new double[pixel * pixel];

	double xre = 0, yre = 0;
	double BRre;
	Complex complexTempRec;
	Complex complexKRec;
	Complex complexPixelRec;
	Complex pixelValue;
	int IpixelValue;
	int imageRec[pixel * pixel];

	for (int pixelRowre = 0; pixelRowre < pixel; pixelRowre++){
		for (int pixelColre = 0; pixelColre < pixel; pixelColre++){
			xre = -1 + (2 / pixel) * pixelColre + (1 / pixel);
			yre = 1 - (2 / pixel) * pixelRowre - (1 / pixel);
			rKRec[pixelRowre * pixel + pixelColre] = sqrt(xre * xre + yre * yre);
			cosKRec[pixelRowre * pixel + pixelColre] = xre / rKRec[pixelRowre * pixel + pixelColre];
			sinKRec[pixelRowre * pixel + pixelColre] = yre / rKRec[pixelRowre * pixel + pixelColre];

		}
	}


	for (int pixelIndex = 0; pixelIndex < pixel * pixel; pixelIndex++){
		if (imgData[pixelIndex] < 0){
			imageRec[pixelIndex] = 0;
			continue;
		}

		for (int i = 1; i <= N; i++){
			BRre = bessj1(rKRec[pixelIndex] * Zn[i - 1]);

			for (int j = 0; j < 2 * M + 1; j++){

				if (j < M){
					complexTempRec.real = cosKRec[pixelIndex];
					complexTempRec.imag = -sinKRec[pixelIndex];
					complexTempRec = complexTempRec.power(M - j);
					complexTempRec.real = complexTempRec.real * BRre;
					complexTempRec.imag = complexTempRec.imag * BRre;
					complexKRec = MMoment[(i - 1)* (2 * M + 1) + j] * complexTempRec;
					pixelValue = pixelValue + complexKRec;
				}

				else if (j >M){
					complexTempRec.real = cosKRec[pixelIndex];
					complexTempRec.imag = sinKRec[pixelIndex];
					complexTempRec = complexTempRec.power(j - M);
					complexTempRec.real = complexTempRec.real * BRre;
					complexTempRec.imag = complexTempRec.imag * BRre;
					complexKRec = MMoment[(i - 1)* (2 * M + 1) + j] * complexTempRec;
					pixelValue = pixelValue + complexKRec;
				}

				else if (j == M){
					complexKRec.real = MMoment[(i - 1)* (2 * M + 1) + j].real * BRre;
					complexKRec.imag = MMoment[(i - 1)* (2 * M + 1) + j].imag * BRre;
					pixelValue = pixelValue + complexKRec;
				}
			}
		}
		IpixelValue = int(pixelValue.real);
		imageRec[pixelIndex] = IpixelValue;
		pixelValue.real = 0;
		pixelValue.imag = 0;
	}


	ofstream outfile("ImageReconstruction.txt");
	for (int fp = 0; fp < pixel * pixel; fp++){
		outfile << imageRec[fp] << " ";
		if ((fp + 1) % pixel == 0){
			outfile << endl;
		}
	}
	outfile.close();

	delete[] cosKRec;
	delete[] sinKRec;
	delete[] rKRec;
}
