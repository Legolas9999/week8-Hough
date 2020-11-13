#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;


int main() {
	//------------------------Á·Ï°1£ºÐý×ª-----------------------------
	Mat len;
	Mat len_trans;
	len = imread("len.jpg");
	imshow("",len);
	Point2f center(len.cols/2.0,len.rows/2.0);
	double scale = 1;
	double angle = -10;
	Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	Rect bbox = RotatedRect(center,len.size(),angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height/ 2.0 - center.y;
	warpAffine(len,len_trans,rot,bbox.size());
	imshow("trans",len_trans);
	

	//-----------------------Á·Ï°2Hou-------------------------------------------
	Mat part;
	Mat canny;              

	part = imread("18.jpg", 1);
	Canny(part, canny, 20, 120, 3, false);
	imshow("",canny);
	std::vector<cv::Vec2f> lines;
	HoughLines(canny,lines,1,CV_PI/180,100);
	std::vector<cv::Vec2f>::iterator it = lines.begin();

	for (;it!=lines.end(); ++it)
	{
		Point pt1;
		Point pt2;
		float rho = (*it)[0], theat = (*it)[1];
		double a = cos(theat);
		double b = sin(theat);
		double x0 = a*rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv:: line(part, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);

	}
	imshow("Hou", part);

	//---------------------Á·Ï°3HouP----------------------------------------------
	
	std::vector<cv::Vec4i> liness;
	Mat part2;
	
	part2 = imread("18.jpg", 1);


	HoughLinesP(canny,liness,1,CV_PI/180,30,50,10);
	std::vector<cv::Vec4i>::iterator its = liness.begin();
	
	for (; its != liness.end(); ++its)
	{
		Point pt1;
		Point pt2;
		
		pt1.x = (*its)[0];
		pt1.y = (*its)[1];
		pt2.x = (*its)[2];
		pt2.y = (*its)[3];
		cv::line(part2, pt1, pt2, Scalar(0, 0, 255), 2, CV_AA);

	}
	imshow("HouP", part2);

	waitKey(0);
}