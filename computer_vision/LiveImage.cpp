#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int main() {

cv::VideoCapture cap(0); // camera 0

cv::Mat image;

while (true)
{
cap >> image;
cv::flip(image,image, 1);
cv::imshow("Live Video Stream", image);
cv::waitKey(1);
}
return 0;
}