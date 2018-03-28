#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {

    Mat frizzy = imread("../images/frizzy.png", 0);
    Mat froomer = imread("../images/froomer.png", 0);

    imshow("Frizzy", frizzy);
    imshow("Froomer", froomer);

    Mat frizzyEdge;
    Mat froomerEdge;

    Canny(frizzy, frizzyEdge, 20, 100);
    Canny(froomer, froomerEdge, 20, 100);

    imshow("Frizzy Edge", frizzyEdge);
    imshow("Froomer Edge", froomerEdge);

    Mat common;
    multiply(frizzyEdge, froomerEdge, common);

    imshow("Common", common);

    waitKey(0);

    return 0;
}
