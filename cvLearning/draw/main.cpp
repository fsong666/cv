#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

int main(){

	Mat src(800, 800 ,CV_32FC3, Scalar(0,0,0) );
	Point a(10,10 ), b(300,300),c, d(500,500 );

	line(src, a, b, Scalar(255,0,0), 4 , 0 );
	rectangle(src, a, b, Scalar(255,0,0), 4 , 0 );
	
	c.x = (b.x - a.x) / 2;
	c.y = (b.y - a.y) / 2;
    circle(src, d, 200, Scalar(0,255,0), 4, 4);
    Size sz(200, 200);
    ellipse(src, d, sz, 0, 30, 180, Scalar(123,0,221), 4, 4);
    ellipse(src, d, Size(200,100), 0, 0, -90, Scalar(123,220,0), 4, 4);
    ellipse(src, d, Size(200,100), 0, -90, -180, Scalar(123,220,255), 4, 4);

    Point e(100, 50 ),f(300,10);
    Point pts[]={a, f,e,a};
    int npts[] = {4 };
    fillConvexPoly(src, pts, npts[0], Scalar(0,255,0), 4 );

    String str("wer bist du ");
    putText(src, str, b, FONT_HERSHEY_SIMPLEX, 2, Scalar(255,255,255),4,4,false );

    RNG rng;
    double aa = rng.uniform(0.0, 10.0);

    cout << aa << endl;

	imshow("src", src );
	waitKey();

	return 0;
}
