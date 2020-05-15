#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void SaltAndPepper(cv::Mat &image, int n)
{
    for(int k=0;k<n;k++)
    {
        int i=rand()%image.cols;//random value 0-imge.cols;
        int j=rand()%image.rows;


        image.at<uchar>(i, j) = 255;
        image.at<cv::Vec3b>(i, j)[1] = 255;
        image.at<cv::Vec3b>(i, j)[2] = 255;
    }   
    for(int k=0;k<n;k++)
    {   
        int i=rand()%image.cols;
        int j=rand()%image.rows;
    
       image.at<uchar>(i, j) = 0;
       image.at<cv::Vec3b>(i, j)[1] = 0;
       image.at<cv::Vec3b>(i, j)[2] = 0;
    }   
}

void Gradient(Mat &src, Mat &gradient ){

	unsigned char gx, gy;	
	for(int y = 0; y < src.rows ; y++){
		for(int x = 0; x < src.cols; x++ ){
			gx = abs( src.at<uchar>(y+1,x ) - src.at<uchar>(y, x ) );
			gy = abs( src.at<uchar>(y ,x+1 ) - src.at<uchar>(y, x ) );
			gradient.at<uchar>(y, x ) = gx + gy;  
			
		}
	}
	
	imshow("gradient", gradient );
}

template<typename _Tp>
vector<_Tp> convertMatVec(const Mat &mat)
{
	return (vector<_Tp>)(mat.reshape(1, 1));//通道数不变，按行转为一行
}


/*
void NMS(Mat &src, Mat &dst ){
	
	uchar max= 0;
	for(int j = 0; j < src.rows ; j++){
		for(int k = 0; k < src.cols; k++ ){
			if(src.at<uchar>(j, k) > src.at<uchar>(j, k + 1 )   ){
				if(src.at<uchar>(j,k) > src.at<uchar>(j, k - 1  )  ){
					dst.at<uchar>(j, k) = src.at<uchar>(j, k );
				}else{
					dst.at<uchar>(j, k) = src.at<uchar>(j, k - 1);
				}
			}else if(src.at<uchar>(j, k + 1 ) >  ) {
					dst.at<uchar>(j, k) = src.at<uchar>(j, k + 1);
			}
			
		}
	}

}*/

Mat NMS2(Mat &src, int size ){

	Mat dst(src.size(), src.type(), Scalar::all(0) );
	int border = size / 2 ;

	for(int j = border ; j < src.rows - border ; j++ ){
		for(int k = border;k < src.cols - border ; k++  ){
			
			Mat window;
		
			src( Rect( k-size /2 , j-size /2 ,size , size) ).copyTo(window);
			
			vector<uchar> vec = convertMatVec<uchar>(window );
			std::sort(vec.begin(), vec.end() );	
			dst.at<uchar>(j, k) = vec[size*size - 1];//max value copy to dst		
		}
	
	}
	return dst;

}
void mySobel(Mat &src, Mat &dst ){

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, abs_dst;

	//sobel-x
	Sobel(src, grad_x, CV_16S, 1, 0 , 3 , 1   );
	convertScaleAbs( grad_x, abs_grad_x );
//	imshow("Sobel-x", abs_grad_x );
	//sobel-y
	Sobel(src, grad_y, CV_16S, 0, 1 , 3 , 1   );
	convertScaleAbs( grad_y, abs_grad_y );
//	imshow("Sobel-y", abs_grad_y );
	//sobel-xy
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
	imshow("Sobel", dst);

}

int main(){

	Mat gray, src = imread("lena.jpg");
	Mat src2 = src.clone( );
	if(src.empty() )
		return -1;
	Mat gradient = Mat::zeros(src.size(), CV_8UC1 );
	Mat dst = gradient.clone( );
	Mat abs_grad_x, abs_grad_y, abs_dst;
	
	SaltAndPepper( src, 500);
	cvtColor( src, gray, CV_BGR2GRAY );
	imshow("src_gray ", gray );

//	Gradient(gray, gradient );
//	dst = gray + gradient;
//	imshow("gradient + gray", dst );

	//nach filter von Gaussfilter
	GaussianBlur(gray, gray,Size(3,3), 0 , 0 );
	imshow("gray nach filter ", gray );

//	GaussianBlur(gray, gray,Size(3,3), 0 , 0 );
	Gradient(gray, gradient );
	dst = gray + gradient;
	imshow("gradient + gray2 ", dst );
	src.copyTo(dst, gradient);
	imshow("gradient !! ", dst );// schawrz punnkt == punkt of gradient = 0 no Veranderung
	
	Mat nms = NMS2(gradient, 3 );
	imshow("NMS", nms);

	mySobel(src,dst );
	
	Laplacian( src, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( dst, abs_dst );
	imshow("Laplacian", abs_dst);

	Canny(src, dst, 150, 100, 3 );
	imshow("Canny", dst);

	src.copyTo(dst, dst);//src & dst => dst  dst als maske
	imshow("Canny2", dst);
	waitKey(0);
	return 0;
}
