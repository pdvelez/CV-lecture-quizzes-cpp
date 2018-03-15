/*
Code that demonstrates how a template can be found by performing a 2D cross
correlation.

Required libraries:
- opencv
- dlib
*/

#include <iostream>
#include <vector>
#include <limits>

#include <dlib/opencv.h>
#include <dlib/matrix.h>
#include <dlib/image_io.h>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
using namespace dlib;

std::vector<int> findTemplate2D(const Mat&, const Mat&);
matrix<float> cv2DMatTo2DdlibMatrix(const Mat&);
std::vector<int> matrixArgMax(const matrix<float>&);

int main(int argc, char const *argv[]) {

    Mat tablet = imread("../images/tablet.png", 0);

    if (tablet.empty()){
        cout << "Error loading the moon image." << endl;
        return -1;
    }

    imshow("Tablet", tablet);

    Mat glyph(tablet, Rect(149, 74, 184-149, 165-74));

    imshow("Glyph", glyph);

    Scalar tempVal;
    tempVal = mean(tablet);

    float tabletMean = tempVal.val[0];

    tempVal = mean(glyph);
    float glyphMean = tempVal.val[0];

    Mat tablet2;
    tablet.convertTo(tablet2, CV_32F);
    tablet2 = tablet2 - tabletMean;

    Mat glyph2;
    glyph.convertTo(glyph2, CV_32F);
    glyph2 = glyph2 - glyphMean;

    std::vector<int> rawIndex = findTemplate2D(glyph2, tablet2);

    Mat tabletRGB;
    cv::cvtColor(tablet, tabletRGB, cv::COLOR_GRAY2BGR);

    cv::rectangle(tabletRGB,
              cv::Point(rawIndex[1], rawIndex[0]),
              cv::Point(rawIndex[1] + glyph.cols, rawIndex[0] + glyph.rows),
              cv::Scalar(0, 0, 255),
              2
             );

    imshow("Glyph found", tabletRGB);

    waitKey(0);

    return 0;
}

matrix<float> cv2DMatTo2DdlibMatrix(const Mat& cvMatObject)
{
    const int rows = cvMatObject.rows;
    const int cols = cvMatObject.cols;

    matrix<float> outMatrix;
    outMatrix.set_size(rows, cols);

    for (int i = 0; i < outMatrix.nr(); i++)
    {
        for (int j = 0; j < outMatrix.nc(); j++)
        {
            outMatrix(i, j) = cvMatObject.at<float>(i, j);
        }
    }

    return outMatrix;
}

std::vector<int> matrixArgMax(const matrix<float>& inputMatrix)
{
    int maxVal = std::numeric_limits<int>::min();
    int maxRow = 0;
    int maxCol = 0;

    for (int i = 0; i < inputMatrix.nr(); i++)
    {
        for (int j = 0; j < inputMatrix.nc(); j++)
        {
            int tempVal = inputMatrix(i, j);

            if (tempVal > maxVal)
            {
                maxVal = tempVal;
                maxRow = i;
                maxCol = j;
            }

        }
    }

    std::vector<int> argMax;

    argMax = {maxRow, maxCol};

    return argMax;
}


std::vector<int> findTemplate2D(const Mat& imgMat, const Mat& templateMat)
{
    matrix<float> imgMatrix;
    imgMatrix = cv2DMatTo2DdlibMatrix(imgMat);

    matrix<float> templateMatrix;
    templateMatrix = cv2DMatTo2DdlibMatrix(templateMat);

    matrix<float> corr2DVals;
    corr2DVals = xcorr_valid(templateMatrix, imgMatrix);

    std::vector<int> index2D = matrixArgMax(corr2DVals);

    return index2D;
}
