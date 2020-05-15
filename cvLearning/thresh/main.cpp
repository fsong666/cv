#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>



using namespace std;
using namespace cv;

bool BINARY = false;
bool TOZERO = false;

void sum(Mat &src, Mat &dst , bool ARG  ){
	
	vector< cv::Mat> planes;
	split(src, planes );
	Mat s, b = planes[0], g = planes[1], r = planes[2];

	addWeighted(r, 1./3, g, 1./3, 0.0, s );//s = r/3 + g/3 + b/3
	addWeighted(s, 1., b, 1./3, 0.0, s );
	cout << s.channels();	
	imshow("s", s );
	if(ARG && !TOZERO ){
		threshold(s, dst, 15, 255, THRESH_BINARY_INV );// dst > 125 ? max : 0
		cout<< "fiif "<< endl;
	}else if(ARG && !BINARY ){
		threshold(s, dst, 15, 255, THRESH_TOZERO );//dst > 125 ? SRC : 0
		cout<<"second "<< endl;
	}else{
		cout << "adaptive"<< endl;
		adaptiveThreshold(s, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV  , 71, 15 );
	
	}
}


int main(){
	
	Mat dst, src = imread("123.jpg");
	if(src.empty() ) 
		return -1;
	BINARY = true;
	sum(src, dst,BINARY );
	imshow("src", src);
	imshow("BINARY", dst);
	BINARY = false;

	TOZERO = true;
	sum(src, dst,TOZERO );
	imshow("TOZERO", dst);
//	TOZERO = false;

	BINARY = true;
	bool aa = true;
	sum(src,dst,aa );	

	imshow("adpative", dst);

	waitKey(0);
	return 0;

}
