#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;
//process image and coefficient data using file processing method and opencv

//read image data from .txt file
int* readImgData(int pixel)
{
	int *readImgData = new int[pixel * pixel];
	ifstream img("ImageData.txt");    //open file
	//read data
	for (int i = 0; i < pixel * pixel; i++){
		img >> readImgData[i];
	}
	img.close();//close file
	return readImgData;
}

//read An data in memory
double* readAn()
{
	double *readAn = new double[200];
	fstream readAnm;
	readAnm.open("readAn.txt", ios::in);
	while (!readAnm.eof()){
		string readAnChar;
		for (int i = 0; i < 200; i++){
			readAnm >> readAnChar;
			const char*temp = readAnChar.c_str();
			readAn[i] = atof(temp);
		}
	}
	readAnm.close();
	return readAn;
}

//read Zn data in memory
double* readZn()
{
	double *readZn = new double[200];
	fstream Zeron;
	Zeron.open("Zeron.txt", ios::in);
	while (!Zeron.eof()){
		string ZeronChar;
		for (int i = 0; i < 200; i++){
			Zeron >> ZeronChar;
			const char*temp = ZeronChar.c_str();
			readZn[i] = atof(temp);
			//cout << readZn[i] << endl;
		}
	}
	Zeron.close();
	return readZn;
}

//using opencv get the image data
void readImage(int pixel)
{
	char* imgName;
	int pixel;

	cout << "Please input the image name";
	cin >> imgName;
	Mat src = imread(imgName, 0);
	Mat img;
	resize(src, img, Size(pixel, pixel));

	int *ImgData = new int[pixel * pixel];
	for (int i = 0; i < pixel; i++){
		for (int j = 0; j < pixel; j++){
			*(ImgData + i * pixel + j) = (int)img.at<uchar>(i, j);
		}
	}

	ofstream outfile("ImageData.txt", ios::in | ios::trunc);
	for (int i = 0; i < pixel * pixel; i++){
		outfile << *(ImgData + i) << "";
	}
}