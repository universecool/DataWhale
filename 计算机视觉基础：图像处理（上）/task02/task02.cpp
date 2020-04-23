#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void affine_trans_translation(cv::Mat& src, cv::Mat& dst, double tx, double ty);
void affine_trans_translation(cv::Mat& src, cv::Mat& dst, double tx, double ty);

int main()
{
    //旋转1
    Mat src = imread("lenna.jpg");
	Mat dst;
 
	//旋转角度
	double angle = 45;
 
	Size src_sz = src.size();
	Size dst_sz(src_sz.height, src_sz.width);
	int len = std::max(src.cols, src.rows);
 
	//指定旋转中心（图像中点）
	Point2f center(len / 2., len / 2.);
	
	//获取旋转矩阵（2x3矩阵）
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
 
	//根据旋转矩阵进行仿射变换
	warpAffine(src, dst, rot_mat, dst_sz);
 
	//显示旋转效果
	imshow("image", src);
	imshow("result", dst);
 
	waitKey(0);

    //平移1
	Mat src = imread("lenna.jpg");
	Mat dst;
 
	Size dst_sz = src.size();
	
	//定义平移矩阵
	Mat t_mat =Mat::zeros(2, 3, CV_32FC1);
 
	t_mat.at<float>(0, 0) = 1;
	t_mat.at<float>(0, 2) = 20; //水平平移量
	t_mat.at<float>(1, 1) = 1;
	t_mat.at<float>(1, 2) = 10; //竖直平移量
 
	//根据平移矩阵进行仿射变换
	warpAffine(src, dst, t_mat, dst_sz);
 
	//显示平移效果
	imshow("image", src);
	imshow("result", dst);
 
	waitKey(0);

    //平移2
    Mat src = imread("lenna.jpg");
	Mat dst;
    affine_trans_rotate(src, dst, angle)

    //旋转2
    Mat src = imread("lenna.jpg");
	Mat dst;
    affine_trans_translation(src, dst, 20, 10)

    return 0；
 
}

/*图像旋转（以图像中心为旋转中心）*/
void affine_trans_translation(cv::Mat& src, cv::Mat& dst, double tx, double ty){
	double angle = Angle*CV_PI / 180.0;
	//构造输出图像
	int dst_rows = round(fabs(src.rows * cos(angle)) + fabs(src.cols * sin(angle)));//图像高度
	int dst_cols = round(fabs(src.cols * cos(angle)) + fabs(src.rows * sin(angle)));//图像宽度
 
	if (src.channels() == 1) {
		dst = cv::Mat::zeros(dst_rows, dst_cols, CV_8UC1); //灰度图初始
	} 
	else {
		dst = cv::Mat::zeros(dst_rows, dst_cols, CV_8UC3); //RGB图初始
	}
 
	cv::Mat T1 = (cv::Mat_<double>(3,3) << 1.0,0.0,0.0 , 0.0,-1.0,0.0, -0.5*src.cols , 0.5*src.rows , 1.0); // 将原图像坐标映射到数学笛卡尔坐标
	cv::Mat T2 = (cv::Mat_<double>(3,3) << cos(angle),-sin(angle),0.0 , sin(angle), cos(angle),0.0, 0.0,0.0,1.0); //数学笛卡尔坐标下顺时针旋转的变换矩阵
	double t3[3][3] = { { 1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.5*dst.cols, 0.5*dst.rows ,1.0} }; // 将数学笛卡尔坐标映射到旋转后的图像坐标
	cv::Mat T3 = cv::Mat(3.0,3.0,CV_64FC1,t3);
	cv::Mat T = T1*T2*T3;
	cv::Mat T_inv = T.inv(); // 求逆矩阵
 
	for (double i = 0.0; i < dst.rows; i++){
		for (double j = 0.0; j < dst.cols; j++){
			cv::Mat dst_coordinate = (cv::Mat_<double>(1, 3) << j, i, 1.0);
			cv::Mat src_coordinate = dst_coordinate * T_inv;
			double v = src_coordinate.at<double>(0, 0); // 原图像的横坐标，列，宽
			double w = src_coordinate.at<double>(0, 1); // 原图像的纵坐标，行，高
		//	std::cout << v << std::endl;
 
			/*双线性插值*/
			// 判断是否越界
			if (int(Angle) % 90 == 0) {
				if (v < 0) v = 0; if (v > src.cols - 1) v = src.cols - 1;
				if (w < 0) w = 0; if (w > src.rows - 1) w = src.rows - 1; //必须要加上，否则会出现边界问题
			}
 
			if (v >= 0 && w >= 0 && v <= src.cols - 1 && w <= src.rows - 1){
				int top = floor(w), bottom = ceil(w), left = floor(v), right = ceil(v); //与映射到原图坐标相邻的四个像素点的坐标
				double pw = w - top ; //pw为坐标 行 的小数部分(坐标偏差)
				double pv = v - left; //pv为坐标 列 的小数部分(坐标偏差)
				if (src.channels() == 1){
					//灰度图像
					dst.at<uchar>(i, j) = (1 - pw)*(1 - pv)*src.at<uchar>(top, left) + (1 - pw)*pv*src.at<uchar>(top, right) + pw*(1 - pv)*src.at<uchar>(bottom, left) + pw*pv*src.at<uchar>(bottom, right);
				}
				else{
					//彩色图像
					dst.at<cv::Vec3b>(i, j)[0] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[0] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[0] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[0] + pw*pv*src.at<cv::Vec3b>(bottom, right)[0];
					dst.at<cv::Vec3b>(i, j)[1] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[1] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[1] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[1] + pw*pv*src.at<cv::Vec3b>(bottom, right)[1];
					dst.at<cv::Vec3b>(i, j)[2] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[2] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[2] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[2] + pw*pv*src.at<cv::Vec3b>(bottom, right)[2];
				}
			}
		}
	}
}


/*平移变换*（以图像左顶点为原点）/
/****************************************
tx: 水平平移距离 正数向右移动 负数向左移动
ty: 垂直平移距离 正数向下移动 负数向上移动
*****************************************/
void affine_trans_translation(cv::Mat& src, cv::Mat& dst, double tx, double ty){
	//构造输出图像
	int dst_rows = src.rows;//图像高度
	int dst_cols = src.cols;//图像宽度
 
	if (src.channels() == 1) {
		dst = cv::Mat::zeros(dst_rows, dst_cols, CV_8UC1); //灰度图初始
	}
	else {
		dst = cv::Mat::zeros(dst_rows, dst_cols, CV_8UC3); //RGB图初始
	}
 
	cv::Mat T = (cv::Mat_<double>(3, 3) << 1,0,0 , 0,1,0 , tx,ty,1); //平移变换矩阵
	cv::Mat T_inv = T.inv(); // 求逆矩阵
 
	for (int i = 0; i < dst.rows; i++){
		for (int j = 0; j < dst.cols; j++){
			cv::Mat dst_coordinate = (cv::Mat_<double>(1, 3) << j, i, 1);
			cv::Mat src_coordinate = dst_coordinate * T_inv;
			double v = src_coordinate.at<double>(0, 0); // 原图像的横坐标，列，宽
			double w = src_coordinate.at<double>(0, 1); // 原图像的纵坐标，行，高
 
			/*双线性插值*/
			// 判断是否越界
 
			if (v >= 0 && w >= 0 && v <= src.cols - 1 && w <= src.rows - 1){
				int top = floor(w), bottom = ceil(w), left = floor(v), right = ceil(v); //与映射到原图坐标相邻的四个像素点的坐标
				double pw = w - top; //pw为坐标 行 的小数部分(坐标偏差)
				double pv = v - left; //pv为坐标 列 的小数部分(坐标偏差)
				if (src.channels() == 1){
					//灰度图像
					dst.at<uchar>(i, j) = (1 - pw)*(1 - pv)*src.at<uchar>(top, left) + (1 - pw)*pv*src.at<uchar>(top, right) + pw*(1 - pv)*src.at<uchar>(bottom, left) + pw*pv*src.at<uchar>(bottom, right);
				}
				else{
					//彩色图像
					dst.at<cv::Vec3b>(i, j)[0] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[0] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[0] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[0] + pw*pv*src.at<cv::Vec3b>(bottom, right)[0];
					dst.at<cv::Vec3b>(i, j)[1] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[1] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[1] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[1] + pw*pv*src.at<cv::Vec3b>(bottom, right)[1];
					dst.at<cv::Vec3b>(i, j)[2] = (1 - pw)*(1 - pv)*src.at<cv::Vec3b>(top, left)[2] + (1 - pw)*pv*src.at<cv::Vec3b>(top, right)[2] + pw*(1 - pv)*src.at<cv::Vec3b>(bottom, left)[2] + pw*pv*src.at<cv::Vec3b>(bottom, right)[2];
				}
			}
		}
	}
}