#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

#define PI 3.14159265

Mat cvMatAtan2(const Mat&, const Mat&);
Mat selectGdir(const Mat&,  const Mat&, const int&, const int&, const int&);

int main(int argc, char const *argv[]) {

    Mat img = imread("../images/octagon.png", 0);

    imshow("Image", img);

    Mat imgFloat;
    img.convertTo(imgFloat, CV_32F);

    imgFloat = imgFloat / 255;

    Mat gX;
    Sobel(imgFloat, gX, -1, 1, 0);

    Mat gY;
    Sobel(imgFloat, gY, -1, 0, 1);

    imshow("gX", gX);
    imshow("gY", gY);

    Mat gXPow;
    pow(gX, 2, gXPow);

    Mat gYPow;
    pow(gY, 2, gYPow);

    Mat tmpMat = gXPow + gYPow;

    Mat gMag;
    sqrt(tmpMat, gMag);

    Mat gDir;
    gDir = cvMatAtan2(gX, gY);

    Mat gDirNorm;
    normalize(gDir, gDirNorm, 0, 255, NORM_MINMAX, CV_8UC1);

    imshow("Gmag", gMag / (4 * sqrt(2)));
    imshow("Gdir", gDirNorm);

    Mat myGrad = selectGdir(gMag, gDir, 1, 30, 60);
    imshow("My Grad", myGrad);

    waitKey(0);

    return 0;
}

Mat cvMatAtan2(const Mat& xMat, const Mat& yMat)
{
    Mat outputMat = Mat::zeros(xMat.rows, xMat.cols, CV_32F);

    for (int i = 0; i < xMat.rows; i++)
    {
        for (int j = 0; j < xMat.cols; j++)
        {
            outputMat.at<float>(i, j) = atan2(-yMat.at<float>(i, j), xMat.at<float>(i, j)) * 180 / PI;
        }
    }

    return outputMat;
}

Mat selectGdir(const Mat& gradMag,  const Mat& gradDir, const int& magMin, const int& angleLow, const int& angleHigh)
{

    Mat outputMat = gradMag >= magMin;
    outputMat = outputMat & (gradDir >= angleLow);
    outputMat = outputMat & (gradDir <= angleHigh);

    return outputMat;
}
