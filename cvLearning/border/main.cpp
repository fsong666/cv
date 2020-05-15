#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
	
	Mat img = imread("lena.jpg");
	if(img.empty() )	return -1;
	Mat dst(img.rows + 100, img.cols + 100, img.type()  );
	img.copyTo(dst );
	imshow("dst",dst );
	Mat dst2;
	imshow("img",img );

	copyMakeBorder(dst, dst2, 0 , 50, 0,  50, BORDER_WRAP  );
	imshow("WRAP",dst2 );

	copyMakeBorder(dst, dst2, 0 , 50, 0,  50, BORDER_CONSTANT, Scalar:: all(125)  );//all(125)==Scalar(125,125,125)
	imshow("CONSTANT",dst2 );
	
	copyMakeBorder(dst, dst2, 0 , 50, 0,  50, BORDER_REPLICATE );
	imshow("REPLICATE",dst2 );

	copyMakeBorder(dst, dst2, 0 , 50, 0,  50, BORDER_REFLECT_101 );
	imshow("REFLECT",dst2 );


	waitKey(0);

	return 0;
}
