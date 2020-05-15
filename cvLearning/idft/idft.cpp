#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
Mat  DFT(Mat img, int flag ){
    int m = getOptimalDFTSize(img.rows );
    int n = getOptimalDFTSize(img.cols );
    Mat padded;
    copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
    Mat complex_img;
    merge(planes, 2, complex_img );

    dft( complex_img, complex_img );
    split(complex_img, planes); //planes[] is Arry of Mat with 1 Chanels, planes[0]=real,planes[1]=Rem;
    magnitude(planes[0], planes[1], planes[0]);//magnitude = planes[0]
    Mat mag_img = planes[0];

    mag_img += Scalar::all(1);
    log( mag_img, mag_img);
    mag_img = mag_img(Rect(0, 0, mag_img.cols&-2, mag_img.rows&-2) );

//    imshow("DFT1 img ", mag_img);

    int cx = mag_img.cols / 2;
    int cy = mag_img.rows / 2;
    Mat q0(mag_img, Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    Mat q1(mag_img, Rect(cx, 0, cx, cy));      //右上角图像
    Mat q2(mag_img, Rect(0, cy, cx, cy));      //左下角图像
    Mat q3(mag_img, Rect(cx, cy, cx, cy));
 //变换左上角和右下角象限
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
    normalize(mag_img, mag_img, 0, 1, CV_MINMAX);

//	Mat DFT_img[] = {mag_img, complex_img  };
	if (flag == 0){
		return mag_img;
	}else{
		return complex_img;
	}

}

int main(int argc, char** argv){
	Mat img = imread(argv[1], IMREAD_GRAYSCALE );
    if (img.empty() ) return -1;
    imshow("input img ", img);
	Mat  magDFT = DFT (img,0);
	Mat  complexDFT = DFT(img, 1);
    imshow("DFT img ",magDFT);
	
	Mat iDft[]={Mat::zeros(magDFT.size(),CV_32F),Mat::zeros(magDFT.size(),CV_32F)};
	idft( complexDFT, complexDFT, DFT_SCALE  );
	split( complexDFT, iDft );
//	magnitude(iDft[0],iDft[1],iDft[0]);//分离通道，主要获取0通道
	normalize(iDft[0],iDft[0],0,1,CV_MINMAX);//归一化处理，float类型的显示范围为0-1,大于1为白色，小于0为黑色
	imshow("idft_Real",iDft[0]);
	normalize(iDft[1],iDft[1],0,1,CV_MINMAX);//ImPart output 
	imshow("idft_Im",iDft[1]);
	waitKey(0);
	destroyAllWindows();
	return 0;
}





