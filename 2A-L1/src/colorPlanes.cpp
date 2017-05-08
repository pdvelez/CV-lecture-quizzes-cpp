
#include "colorPlanes.h"

int colorPlanes(void) {
    std::cout << "Running Color Planes..." << std::endl;

    // Read the input image
    cv::Mat fruit = cv::imread("../images/fruit.png", CV_LOAD_IMAGE_UNCHANGED);

    if (fruit.empty()){
        std::cout << "Error loading the fruit image." << std::endl;
        return -1;
    }

    cv::namedWindow("Fruit Image", CV_WINDOW_AUTOSIZE);
    imshow("Fruit Image", fruit);

    std::cout << "Image shape: " << fruit.size() << std::endl;
    std::cout << "Image columns: " << fruit.cols << std::endl;
    std::cout << "Image rows: " << fruit.rows << std::endl;

    // Red, green, and blue color planes. Remember OpenCV uses BGR
    cv::Mat red, green, blue;

    std::vector<cv::Mat> channels(3);

    split(fruit, channels);

    red = channels[2];
    green = channels[1];
    blue = channels[0];

    cv::namedWindow("Red color plane", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Green color plane", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("Blue color plane", CV_WINDOW_AUTOSIZE);

    imshow("Red color plane", red);
    imshow("Green color plane", green);
    imshow("Blue color plane", blue);

    std::cout << "Green color plane, 100-th row: \n" << green.row(99);

    // Let's draw a horizontal line across that row we picked, just for fun
    // But in order to see the line in color we need to convert green to a 3-channel array
    cv::Mat greenBGR;

    cvtColor(green, greenBGR, CV_GRAY2BGR);

    // You will notice that cv2.line uses x-y coordinates instead of row-cols
    cv::line(greenBGR, cv::Point2i(0, 99), cv::Point2i(greenBGR.cols, 99), cv::Scalar(0, 0, 255));

    cv::namedWindow("100-th row drawn", CV_WINDOW_AUTOSIZE);

    imshow("100-th row drawn", greenBGR);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}
