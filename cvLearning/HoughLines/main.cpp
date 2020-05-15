#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv; 
using namespace std;



int main ( int, char** argv )
{


    // Declare the output variables
    Mat dst, cdst, cdstP;

    // Loads an image
    Mat src = imread( argv[1], IMREAD_GRAYSCALE );  
    //Mat src = imread( "Haus.png", IMREAD_GRAYSCALE );

    // Check if image is loaded fine
    if(src.empty()){
        return -1; 
    }   
    // Edge detection
    Canny(src, dst, 50, 200, 3); 
    // Copy edges to the images that will display the results in BGR
	imshow("Canny",dst);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    // Standard Hough Line Transform
//    vector<Vec2f> lines; // will hold the results of the detection
	 // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 50 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
    // Show results
    imshow("Source", src);
//    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
    // Wait and Exit
    waitKey();
    return 0;
}


