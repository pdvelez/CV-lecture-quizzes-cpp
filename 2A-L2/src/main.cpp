
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


// Customized imshow function to match the quiz
static void imshow(std::string title, cv::Mat image){
    // WARNING: Using a clipping method to get results similar to the quiz.
    // This is NOT a good practice because you are discarding information that is
    // below 0 and above 255. Use normalization instead.

    cv::Mat output = image.clone();

    output.setTo(255, output > 255);
    output.setTo(0, output < 0);

    cv::namedWindow(title);
    cv::imshow(title, output);
}

int main() {

    cv::Mat saturnImage = cv::imread("../images/saturn.png", CV_LOAD_IMAGE_GRAYSCALE);

    if (saturnImage.empty()){
        std::cout << "Error loading the saturn image." << std::endl;
        return -1;
    }

    cv::imshow("Saturn Image", saturnImage);

    // Add some noise
    cv::Mat noisyImage = saturnImage.clone();

    int noiseMean = 0;
    int noiseStddev = 25;
    cv::randn(noisyImage, noiseMean, noiseStddev);

    noisyImage += saturnImage.clone();

    imshow("Noisy Image", noisyImage);

    // Create a Gaussian filter
    int filterSize = 11;
    int filterSigma = 2;

    // OpenCV does not have a fspecial function. Instead we will cv::getGaussianKernel
    // to generate a Gaussian kernel.
    cv::Mat filterKernel = cv::getGaussianKernel(filterSize, filterSigma);

    // Apply it to remove noise
    cv::Mat smoothedImage;

    // We can use sepFilter2D for a faster run. We will use the same filter kernel for X and Y.
    cv::sepFilter2D(noisyImage, smoothedImage, -1, filterKernel, filterKernel);

    imshow("Smoothed Image", smoothedImage);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}