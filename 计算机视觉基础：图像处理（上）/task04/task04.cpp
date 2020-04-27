#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
    //载入图像
    Mat image = imread("1.jpg");
    Mat dst1, dst2, dst3;
    //均值滤波
    blur(image, dst1, Size(7, 7));
    //方框滤波
    boxFilter(image, dst2, -1, Size(7, 7), Point(-1, -1), true, BORDER_CONSTANT);
    //高斯滤波
    GaussianBlur(image, dst3, cv::Size(7, 7), 0.8);

    //创建窗口并显示
    namedWindow("均值滤波效果图");
    namedWindow("方框滤波效果图");
    namedWindow("高斯滤波效果图");
    imshow("均值滤波效果图", dst1);
    imshow("方框滤波效果图", dst2);
    imshow("高斯滤波效果图", dst3);
    imwrite("均值滤波效果图.jpg", dst1);
    imwrite("方框滤波效果图.jpg", dst2);
    imwrite("高斯滤波效果图.jpg", dst3);
    
    waitKey(0);
    return 0;
}