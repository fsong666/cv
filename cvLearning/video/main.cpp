#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;
void processiamge(Mat &frame)
{
	circle(frame, Point(cvRound(frame.cols / 2), cvRound(frame.rows / 2)), 150, Scalar(0, 0, 255), 2, 8);
}


int main(){

	VideoCapture vc("af.mp4");

	double rate = vc.get(cv::CAP_PROP_FPS );
	int delay =cvRound(1000.0 /  rate );// 1/rate second * 1000 = ms
	Mat frame;
	vc >> frame;

	VideoWriter out("outsb2.avi" ,CV_FOURCC('M','J','P','G' ) , rate , frame.size(), true );

	if(!out.isOpened() )
		return -1;
	else{

		if(!vc.isOpened() )
			return -1;
		else{

			while (true)
			{
			vc >> frame;//读出每一帧的图像
			out << frame;
			if (frame.empty()) break;//
			imshow("处理前视频", frame);
			processiamge(frame);
			imshow("处理后视频", frame);
			waitKey( delay );
			}
		}
	}
	return 0;
}


