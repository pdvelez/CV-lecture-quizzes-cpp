
#include "blend2images.h"

/**
 * Blends two images using a weight factor.
 *
 * @param a image A.
 * @param b image B.
 * @param alpha weight factor.
 * @return the blended image.
 */
cv::Mat blend(cv::Mat a, cv::Mat b, float alpha){

    cv::Mat output = a * alpha + (1 - alpha) * b;

    return output;
}

int blend2Images(void) {
    std::cout << "Running Blend Two Images..." << std::endl;

    // Read both input images
    cv::Mat dolphin = cv::imread("../images/dolphin.png", CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat bicycle = cv::imread("../images/bicycle.png", CV_LOAD_IMAGE_UNCHANGED);

    if (dolphin.empty()){
        std::cout << "Error loading the dolphin image." << std::endl;
        return -1;
    }

    if (bicycle.empty()){
        std::cout << "Error loading the bicycle image." << std::endl;
        return -1;
    }

    cv::Mat result = blend(dolphin, bicycle, 0.75);

    cv::namedWindow("Result", CV_WINDOW_AUTOSIZE);
    imshow("Result", result);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}