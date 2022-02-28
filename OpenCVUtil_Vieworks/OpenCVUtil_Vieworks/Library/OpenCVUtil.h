#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <atlstr.h>
using namespace cv;
using namespace std;

class OpenCVUtil
{
public:
	OpenCVUtil();
	virtual ~OpenCVUtil(void);

	Mat SetImagePointer(int Height, int Width, void* pBuffer, int Pixelformat);
	void ImageSave(Mat Image, std::string Name);
	float CalculateImageMean(Mat Source);
	float CalcualteStd(Mat Souce);
};

