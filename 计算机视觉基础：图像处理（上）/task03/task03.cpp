#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

int main( int argc, char** argv )
{
    // Load image
    Mat srcImage = imread("1.jpg"), dstImage;
    
    // RGB2GHSV
    cvtColor(srcImage, dstImage, COLOR_BGR2HSV);
    imshow("Lab Space", dstImage);
    
    //RGB2GRAY
    cvtColor(srcImage, dstImage, COLOR_BGR2GRAY);
    imshow("Gray Scale", dstImage);
    
    waitKey();
    
    return 0;
}