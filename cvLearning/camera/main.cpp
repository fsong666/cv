#include <iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
	
	VideoCapture cap(0);
	double fp = cap.get(CV_CAP_PROP_FPS );
	int delay = cvRound(1000.000 / fp );
	Mat frame;
	cap >> frame;
	VideoWriter out("out.avi",CV_FOURCC('M', 'J', 'P', 'G'), fp, frame.size() );
	cout << fp << " "<< delay << endl;
	while(cap.isOpened()  ){
		cap >> frame;
		out << frame;
		imshow("my",frame );
		if(waitKey(delay ) == 27 ){//return key of 27ascII == "ESC"
			break;
		}
	
	}


	return 0;
}
