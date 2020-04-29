#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat img = imread("1.jpg");
    if (img.empty())
    {
        cout << "Error: Could not load image" << endl;
        return 0;
    }

    Mat gray1;
    cvtColor(img, gray1, CV_BGR2GRAY);

    Mat dst1;
    threshold(gray1, dst1, 0, 255, CV_THRESH_OTSU);

    imshow("src", img);
    imshow("gray1", gray1);
    imshow("�����ֵ", dst1);
    imwrite("�����ֵ.jpg", dst1);


    Mat gray2;
    cvtColor(img, gray2, CV_BGR2GRAY);

    Mat dst2;
    cv::adaptiveThreshold(gray2, dst2, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 21, 10);

    imshow("gray2", gray2);
    imshow("����Ӧ��ֵ", dst2);
    imwrite("����Ӧ��ֵ.jpg", dst1);

    waitKey(0);

    return 0;
}