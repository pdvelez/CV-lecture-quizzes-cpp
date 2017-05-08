
#include "exploreEdgeOptions.h"

int exploreEdgeOptions(){
    std::cout << "Running Explore Edge Options..." << std::endl;

    cv::Mat leavesImage = cv::imread("../images/fall-leaves.png");

    if (leavesImage.empty()){
        std::cout << "Error loading the leaves image." << std::endl;
        return -1;
    }

    cv::imshow("Leaves Image", leavesImage);

    // Create a Gaussian Filter
    int filterSize = 11;
    int filterSigma = 2;

    cv::Mat filterKernel = cv::getGaussianKernel(filterSize, filterSigma);

    // # Apply the kernel using different edge parameters. The ones below mimic what
    // Matlab does. OpenCV has even more options, you should read the cv2.filter2D
    // documentation for more
    methodsMap warpMethods;
    warpMethods["replicate"] = cv::BORDER_CONSTANT;
    warpMethods["symmetric"] = cv::BORDER_REFLECT;
    warpMethods["circular"] = cv::BORDER_WRAP;


    // Define a border method
    std::string method = "circular";

    cv::Mat smoothedImage;

    if (method == "circular"){
        // sepFilter2D does not support cv2.BORDER_WRAP. Instead we create a new image with borders that mirror the
        // edges adding a number of pixels around it equal to filter_size. Then we proceed to filter the image with the
        // Gaussian Kernel. Finally, we crop the blurred image back to the original size removing the added border.

        cv::Mat tempImage;
        cv::copyMakeBorder(leavesImage, tempImage, filterSize, filterSize, filterSize, filterSize, warpMethods[method]);

        cv::sepFilter2D(tempImage, smoothedImage, -1, filterKernel, filterKernel);

        smoothedImage = smoothedImage(cv::Range(filterSize, smoothedImage.rows - filterSize),
                                      cv::Range(filterSize, smoothedImage.cols - filterSize));

    } else {

        cv::sepFilter2D(leavesImage, smoothedImage, -1, filterKernel, filterKernel, cv::Point(-1, -1), 0,
                        warpMethods[method]);

    }

    cv::imshow("Smoothed Image", smoothedImage);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}
