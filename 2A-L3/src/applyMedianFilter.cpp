
#include "applyMedianFilter.h"


cv::Mat imnoise(cv::Mat imageIn, std::string method, float dens){

    cv::Mat noise = cv::Mat(imageIn.rows, imageIn.cols, CV_64F, cvScalar(0.));
    cv::Mat imageOut = imageIn.clone();

    if (method == "salt & pepper"){

        cv::randu(noise, 0, 1);

        imageOut.setTo(0, noise < (dens / 2));
        imageOut.setTo(255, (dens / 2 <= noise & noise < dens));

    }

    return imageOut;
}

int applyMedianFilter(){
    std::cout << "Running Apply Median Filter..." << std::endl;

    cv::Mat moonImage = cv::imread("../images/moon.png", 0);

    if (moonImage.empty()){
        std::cout << "Error loading the moon image." << std::endl;
        return -1;
    }

    cv::imshow("Moon Image", moonImage);

    // Add salt & pepper noise
    cv::Mat noisyImage = imnoise(moonImage, "salt & pepper", 0.02);

    cv::imshow("Noisy Image", noisyImage);

    // Apply a median filter
    cv::Mat medianFiltered;

    cv::medianBlur(noisyImage, medianFiltered, 3);

    cv::imshow("Filtered Image", medianFiltered);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;

}