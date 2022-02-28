#include "OpenCVUtil.h"

OpenCVUtil::OpenCVUtil()
{

}

OpenCVUtil::~OpenCVUtil(void)
{

}

Mat OpenCVUtil::SetImagePointer(int Width, int Height, void* pBuffer,int Pixelformat)
{
	if (Pixelformat == CV_8U)
	{
		Mat ImgContainer(Height, Width, CV_8U, pBuffer);
		return ImgContainer;
	}
}

void OpenCVUtil::ImageSave(Mat Image, std::string Name)
{
	imwrite(Name, Image);
}

float OpenCVUtil::CalculateImageMean(Mat Source)
{
	float m_resIMG_mean = 0;
	Scalar m_scalar = mean(Source);
	m_resIMG_mean = m_scalar[0];
	return m_resIMG_mean;
}

float OpenCVUtil::CalcualteStd(Mat Source)
{
	float m_resIMG_std = 0;
	Scalar mean, stddev;
	meanStdDev(Source, mean, stddev);
	m_resIMG_std = stddev[0];
	return m_resIMG_std;
}