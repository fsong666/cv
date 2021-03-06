#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void SaltAndPepper(cv::Mat &image, int n)
{
    for(int k=0;k<n;k++)
    {
        int i=rand()%image.cols;//random value 0-imge.cols;
        int j=rand()%image.rows;
    
    
        image.at<cv::Vec3b>(i, j)[0] = 255;
        image.at<cv::Vec3b>(i, j)[1] = 255;
        image.at<cv::Vec3b>(i, j)[2] = 255;
    }   
    for(int k=0;k<n;k++)
    {
        int i=rand()%image.cols;
        int j=rand()%image.rows;
    
        image.at<cv::Vec3b>(i, j)[0] = 0;
        image.at<cv::Vec3b>(i, j)[1] = 0;
        image.at<cv::Vec3b>(i, j)[2] = 0;
    }   
}



template<typename _Tp>
vector<_Tp> convertMatVec(const Mat &mat)
{
	return (vector<_Tp>)(mat.reshape(1, 1));//通道数不变，按行转为一行
}

void myMedian(Mat &src, Mat &dst, int size  ){
	int border = size / 2;
	dst = src.clone();
	for(int y = border ; y < src.rows - border ; y++ ){
		for(int x = border;x < src.cols - border ; x++  ){
			
			Mat window;
		
			src( Rect( x-size /2 , y-size /2 ,size , size) ).copyTo(window);
		   	window.reshape(1, 1 );			
			cv::sort(window, window, SORT_EVERY_ROW | SORT_ASCENDING );
			dst.at<uchar>(y, x) = window.at<uchar>(window.rows*window.rows /2  );		
			window.setTo(Scalar(0) );
		}
	
	}


}


void myMedian2(Mat &src1, Mat &dst, int size  ){
	int border = size / 2 ;
	dst = src1.clone();
	for(int y = border ; y < src1.rows - border ; y++ ){
		for(int x = border;x < src1.cols - border ; x++  ){
			
			Mat window;
		
			src1( Rect( x-size /2 , y-size /2 ,size , size) ).copyTo(window);
			
			vector<uchar> vec = convertMatVec<uchar>(window );
			std::sort(vec.begin(), vec.end() );	
			dst.at<uchar>(y, x) = vec[(size*size) /2];		
		}
	
	}


}

void filter( Mat &src, Mat &dst,  Mat &kernel ){
	int	size = kernel.rows;
	int border = size / 2 ;
	src.convertTo(src, CV_32FC1 );
	dst = src.clone();
	cout<< dst.type() << endl;
	cout<< size << endl;
	for(int y = border ; y < src.rows - border ; y++ ){
		for(int x = border;x < src.cols - border ; x++  ){
			
			Mat window;		
			src( Rect( x-size /2 , y-size /2 ,size , size) ).copyTo(window);
	//		window = window.mul( kernel );
			multiply(window, kernel,window, 1, -1  );
			Scalar sum1 = sum( window );
	//		vector<uchar> vec = convertMatVec<uchar>(window );
	//		std::sort(vec.begin(), vec.end() );	
			dst.at<uchar>(y, x) = sum1[0];		
		}
	
	}
	normalize(dst, dst, 0, 1, NORM_MINMAX );

}


int main (int argc, char** argv){

	Mat img ,gray, dst;
	img = imread("lena.jpg" );
	if(img.empty()) return -1;
//	cvtColor(img,img,COLOR_BGR2HSV );
	SaltAndPepper(img, 5000);
//	imshow("input", img );
	
	cvtColor( img, gray, CV_BGR2GRAY );
	imshow("input gray", gray );
	
	double t1 = (double)getTickCount();
	medianBlur(gray, dst,7 );
    t1 = ((double)getTickCount() - t1)/getTickFrequency();
    cout << "time1: " << t1*1000 << "ms" << endl; 
	imshow("medianblur",dst);

	myMedian(gray, dst, 7 );
	imshow("Mymedianblur",dst);
/*
	double t2 = (double)getTickCount();
	myMedian2(gray, dst, 7 );
    t2 = ((double)getTickCount() - t2)/getTickFrequency();
    cout << "time2: " << t2*1000 << "ms" << endl; 
	imshow("Mymedianblur2",dst);
*/
	Mat kernel =(Mat_<float>(3,3) << 1, 1 ,1,
									 1, 1, 1,
			   					     1, 1, 1 );
// 	 kernel =	kernel.mul(1.0 / 9 );

	Mat kernel1 = getGaussianKernel(3, 3, CV_32F);
	kernel1 = kernel1 * kernel1.t();
	cout << kernel1<< endl;

	filter(gray, dst, kernel);

	imshow("filter2d",dst);

	waitKey(0);
	destroyAllWindows();	
	return 0;
}
