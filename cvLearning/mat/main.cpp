#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(){
	Mat img(3, 3, CV_32FC1, Scalar( 3 ) );
	Mat ma = img;
	Mat mb = img.clone();
	cout<<" img=\n" <<img <<endl;

	vector<float> v(3,6),v2;
	v2 =  v;//copy selbst data
	for(auto &i : v )
		cout<< i*i <<",";
	cout << endl;
	for(auto a : v2)
		cout<< a <<",";
	cout << endl;
	Mat m(v, true );// with STL vector create m
	cout<< m <<endl;
	
	img = img.mul(mb);
	addWeighted(img, 2 , mb, 2, 2 , mb );
	cout<<"img=\n"<< img <<endl;
	cout<<"ma=\n  "<< ma <<endl;
	cout<< "addWeight=\n " << mb <<endl;
	divide(20, mb, mb );
	cout<< "divide=\n " << mb << endl;
	cout << "(1,1) = " << int( mb.at< uchar >(1,1) )<< endl;


	cout<<"--------------access---------------------- " << endl;
	cout << "mb = \n " << mb << endl;
	cout << "mb.col(2) =\n  " << mb.col( 2 ) << endl;	
	cout << "mb(Range(0,2 ), Range(0,2 ) ) =\n  " << mb(Range(0 , 2), Range(0, 2 ) ) << endl;
	Mat	ig = mb( Rect(0, 0, 2, 2 )  );// 0 - (2-1) rows 0 - (2-1) cols

	ig = ig.mul(3 );
	cout << "Rect(0,0,3,3) =\n  " << mb( Rect(0, 0 , 3 ,3 ) ) << endl;
	cout << "diag =\n  " << mb.diag( 0 ) << endl;

	cout << "------------Operation of Mat------------------ " << endl;
	Mat mm = img.clone();
	cout << "mm = \n " << mm << endl;
	cout << "mb = \n " << mb << endl;

	//	mm = mm + img;
	cout << "2*(mm + mm - mb)=\n " 
   		 << 2* ( mm + mm - mb )   << endl;
	// Matrix multiplication
	cout << "mm * mb = \n" << mm * mb << endl;
	cout << "t( )=\n "  << mm.t()  << endl;
	cout << "mb.inv( )=\n "  << mb.inv()  << endl;

	cout << "elemnt of  mm * mb = \n" << mm.mul(mb) << endl;
	cout << "element of mm / mb = \n" << mm / mb << endl;
	cout << "element of min(mm,mb) = \n" << min( mm , mb) << endl;


	cout <<"---------mietglied function----------- " << endl;
	cout<<"mb=\n  "<< mb <<endl;

	cout << "setTo(4)=\n "  << mb.setTo( 4 )  << endl;

	mb.convertTo(mb, CV_32FC3 );
	cout << "convertTo(4) =\n "  << mb  << endl;

	Mat inser =  mb.row(2).clone();
    mb.push_back( inser );
	cout << "push_back( mb.row(2))=\n "  << mb  << endl;

	mb.pop_back(2);
	cout << "push_pop(2 )=\n "  << mb << endl;

	mb = mb.reshape(0 , 3);
	cout << "reshape(0, 3)=\n "  << mb << endl;

	Size mbsize;
	Point oft;
	mb.locateROI( mbsize, oft );
	cout << "locateROI\n "  << mbsize << endl;

	cout << "total()=\n "  << mb.total() << endl;

	cout << "elemSize1()=\n "  << mb.elemSize1() <<" Byte " <<endl;
	cout << "elemSize()=\n "  << mb.elemSize() <<" Byte " <<endl;
	
	cout << "type()=\n "  << mb.type() <<endl;
	cout << "depth()=\n "  << mb.depth() <<endl;
	cout << "channels()=\n "  << mb.channels() <<endl;
	cout << "size()=\n "  << mb.size() <<endl;

//	imshow("out", img );
//	imshow("out2", ma );
//	waitKey(0);
	return 0;
}
