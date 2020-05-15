#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void convolutionDFT (Mat A, Mat B, Mat& C){
	C.create(abs(A.rows - B.rows)+1, abs(A.cols - B.cols )+1, A.type());
	Size dftsize;
	dftsize.width  = getOptimalDFTSize(A.cols + B.cols -1 );
    dftsize.height = getOptimalDFTSize(A.rows + B.rows -1 );

	Mat tempA(dftsize, A.type(), Scalar::all(0));
	Mat tempB(dftsize, B.type(), Scalar::all(0));
	
	Mat roiA(tempA, Rect(0, 0, A.cols, A.rows ));
	A.copyTo(roiA );
	Mat roiB(tempB, Rect(0, 0, B.cols, B.rows ));
	B.copyTo(roiB);

	dft(tempA, tempA);
	dft(tempB, tempB);
/*
	Mat tmp = tempB;
    Mat planes[] = { tmp, Mat::zeros(tmp.size(),CV_32F) };
    split(tmp, planes);
    magnitude(planes[0], planes[1], planes[0]);//magnitude = planes[0]
    Mat mag_img = planes[0];

    mag_img += Scalar::all(1);
    log( mag_img, mag_img);
	mag_img = mag_img(Rect(0, 0, mag_img.cols&-2, mag_img.rows&-2) );
    int cx = mag_img.cols / 2;
    int cy = mag_img.rows / 2;
    Mat q0(mag_img, Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    Mat q1(mag_img, Rect(cx, 0, cx, cy));      //右上角图像
    Mat q2(mag_img, Rect(0, cy, cx, cy));      //左下角图像
    Mat q3(mag_img, Rect(cx, cy, cx, cy));

     //变换左上角和右下角象限
    Mat ttmp;
    q0.copyTo(ttmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(ttmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
	
	normalize(mag_img, mag_img, 0, 1, CV_MINMAX);
    imshow("dft", mag_img);
*/	

	mulSpectrums(tempA, tempB,tempA, DFT_COMPLEX_OUTPUT );
/*
	Mat tmp2;
    tempA.copyTo(tmp2);
	Mat planes2[] = { tmp2, Mat::zeros(tmp2.size(),CV_32F) };
	split(tmp2, planes2);
	magnitude(planes2[0], planes2[1], planes2[0]);//magnitude = planes[0]
    Mat mag_img2 = planes2[0];

    mag_img2 += Scalar::all(1);
    log( mag_img2, mag_img2);
	normalize(mag_img2, mag_img2, 0, 1, CV_MINMAX);
	imshow("dft2", mag_img2);
*/	
	dft(tempA, tempA , DFT_INVERSE + DFT_SCALE, C.rows);

	tempA(Rect(0,0, C.cols, C.rows) ).copyTo( C );

}

int main(int argc, char** argv ){
	Mat img = imread(argv[1], IMREAD_GRAYSCALE );
    if (img.empty() ) return -1;
    imshow("input img ", img);

	Mat kernel = (Mat_<float>(3,3)<< 0,1,0,
									 1,1,1,
									 0,1,0 );
	cout << kernel <<endl;
	Mat floatimg = Mat_<float>(img );
	Mat corr;
	convolutionDFT(floatimg, kernel, corr );

	normalize(corr, corr, 0, 1, CV_MINMAX );

	imshow("out", corr );
	waitKey(0);
	destroyAllWindows();
	return 0;

}
