#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void SaltAndPepper(cv::Mat &image, int n)
{
    for(int k=0;k<n;k++)
    {
        int i=rand()%image.cols;//random value 0-imge.cols;
        int j=rand()%image.rows;



    
    
        image.at<cv::Vec3b>(j, i)[0] = 255;
        image.at<cv::Vec3b>(j, i)[1] = 255;
        image.at<cv::Vec3b>(j, i)[2] = 255;
    }   
    for(int k=0;k<n;k++)
    {
        int i=rand()%image.cols;
        int j=rand()%image.rows;
    
        image.at<cv::Vec3b>(j, i)[0] = 0;
        image.at<cv::Vec3b>(j, i)[1] = 0;
        image.at<cv::Vec3b>(j, i)[2] = 0;
    }   
}



int main (int argc, char** argv){

	Mat img,gray;
	img = imread("lena.jpg" );
	if(img.empty()) return -1;
	Mat dst = img.clone();
	SaltAndPepper(img, 5000);
	cvtColor(img, gray, COLOR_BGR2GRAY );
	imshow("input gray", gray);

	//blur mittelwert
	double t = (double)getTickCount();
	blur(img, dst, Size(7, 7 ) );
	t =( (double)getTickCount() - t) / getTickFrequency();
	cout << "blur_t = " << t*1000 << "ms" <<endl;
	imshow("miiterlwert Blur1", dst);

	//median
	t = (double)getTickCount();
	medianBlur(img, dst , 3 );
	t =( (double)getTickCount() - t) / getTickFrequency();
    cout << "median_t = " << t*1000 << "ms" <<endl;
	imshow("medianblur",dst );


	//gaussfilter
	GaussianBlur(img, dst, Size(7 , 7), 0, 0 );
	imshow("gauss", dst);

	//lapalcain
	Laplacian(	dst, dst, -1, 7, 1, 0, BORDER_DEFAULT );
	imshow("LoG", dst);
	
	//bifilter
	Mat outi;
	int d = 3;
	bilateralFilter(gray, outi, d, d*2, d/2,0);
	imshow("bilateral", outi);

	waitKey(0);
	destroyAllWindows();	
	return 0;
}
