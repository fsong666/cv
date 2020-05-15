#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){

    Mat m1(4, 4, CV_32FC1, Scalar(4) );
	Mat m3 , m2(m1.size(), m1.type(), Scalar( 8 ));
    Mat mask = Mat::zeros( m1.size() , CV_8UC1 );
    mask(Rect(1,1, 2,2 ) ).setTo(255);
	cout <<"m1 = \n" << m1 << endl;
	cout <<"m2 = \n" << m2 << endl;
    cout <<"mask = \n" << mask<<"\n"<< endl;

    add(m1, m2, m3, mask );
    cout <<"add(m1 ,m2, m3, mask ) = \n" << m3 << endl;
	absdiff(m2 , m1 , m3);	
	cout <<"absdiff(m2 , m1 ) = \n" << m3 << endl;
	addWeighted(m1, 2, m2 ,1 , 3, m3 );
    cout <<"addWeight =m1*2 + m2*1 + 3 \n"<< m3 <<"\n" << endl;

    bitwise_and(m2 , m1, m3 ,mask);
	cout <<"bitwise_and(m2 , m1 ) = \n" << m3 << endl;
	bitwise_or(m2 , m1, m3 );	
	cout <<"bitwise_or(m2 , m1 ) = \n" << m3 << endl;
	bitwise_xor(m2 , m1, m3 );	
    cout <<"bitwise_xor(m2 , m1 ) = \n" << m3<<"\n" << endl;

	Vec2f v1(1, 0 ), v2(0 , 1), mag, ang;
	cartToPolar(v1, v2, mag, ang ); 
	cout <<"v1 = " << v1 <<" v2=" << v2 << endl;
    cout <<"mag = " << mag <<" ang=" << ang <<"\n"<< endl;

	compare(m1, m2 , m3 , CMP_LT);	
    cout <<"compare(m1 , m2, m3,  CMP_LT ) = \n" << m3 <<"\n"<< endl;
	
	m1.diag(2) = 1;
	m1.diag(3) = 6;
	cout << "m1 = \n"<< m1 << endl;
	completeSymm(m1,false );
    cout << "completeSymm(m1, false)=\n "<< m1<<"\n" << endl;;
    cout << "m1 = \n"<< m1 <<"\n"<< endl;
	
    scaleAdd(m1,0.2, m2, m3);
    cout <<"scaleAdd(m1 ,0.2, m2, m3)=\n "<< m3 <<"\n"<< endl;
	convertScaleAbs(m1, m3, 0.5 , -0.2 );
    cout <<"convertScaleAbs(m1, m3, 0.5 , -0.2)=\n"<< m3 <<"\n"<< endl;

    cout <<"countNonZero(m1)=\n"<<	countNonZero( m1) <<"\n"<< endl;

    cout <<"determinant(m1)=\n"<<	determinant(m1)<<"\n" << endl;
	
	divide(m1, m2, m3 , 0.2 );
    cout <<"divide(m1, m2, m3 , 0.2)=\n"<< m3	<<"\n" << endl;
    cout <<"m2 = \n" << m2 << endl;

    subtract(m1, m2, m3, mask);
    cout <<"subtract(m1, m2, m3, mask )=\n"<< m3 <<"\n"<< endl;

	if(	eigen(m1, m3 ))
        cout <<"eigen(m1, m3 )=\n"<< m3	 <<"\n"<< endl;

    exp(m1, m3 );//m3 = exp(m1)
    cout <<"exp(m1, m3 )=\n"<< m3<<"\n" << endl;

    log(m1, m3);// m3 = log(m1)
    cout <<"log(m1, m3 )=\n"<< m3 <<"\n"<< endl;

    sqrt(m1, m3 );
    cout <<"sqrt(m1, m3 )=\n"<< m3 <<"\n"<< endl;

    pow(m1, 2 , m3 );
    cout <<"pow(m1, 2, m3 )=\n"<< m3 <<"\n"<< endl;

    Scalar sc = sum(m1);
    cout <<"sum(m1)=\n"<< sc[0] <<"\n"<< endl;

    sc = trace(m1);
    cout <<"trace(m1)=\n"<< sc <<"\n"<< endl;

    setIdentity( m1 );
    cout <<"setIdentity( m1 ), m1=\n"<< m1 <<"\n"<< endl;

    sc = mean(m1, mask);
    cout <<"mean(m1, mask)=\n"<< sc <<"\n"<< endl;

    meanStdDev(m1, sc, m3 );
    cout <<"meanStdDev(m1, sc, m3 ),mean=\n"<< sc
        << "\n stddev=\n" << m3 <<"\n"
        << endl;

    multiply(m1, m2 , m3 , 0.1 );
    cout <<"multiply(m1, m2 , m3 , 0.1 )=\n"<< m3 <<"\n"<< endl;

    randu(m1, Scalar(0), Scalar(255) );
    cout <<"randu( m1, Scalar(0), Scalar(255) ), m1=\n"<< m1 <<"\n"<< endl;

    sortIdx(m1, m3, SORT_ASCENDING | SORT_EVERY_COLUMN );
    cout <<"sortIdx(m1, m3, SORT_ASCENDING | SORT_EVERY_COLUMN )\n"<< m3 <<"\n"<< endl;

    randn(m1, 0, 1 );
    cout <<"randn( m1, 0, 1 ), m1=\n"<< m1 <<"\n"<< endl;

    cv::sort(m1, m1,  CV_SORT_EVERY_ROW |CV_SORT_ASCENDING);
    cv::sort(m1, m1,  CV_SORT_EVERY_COLUMN |CV_SORT_ASCENDING);
    cout <<"sort(m1, m1, every cols and rows| SORT_EVERY_COLUMN ) m1=\n"<< m1 <<"\n"<< endl;

    cout <<"max( m1,m2 )=\n"<< max(m1, m2 )<<"\n"<< endl;
    cout <<"min( m1,m2 )=\n"<< min(m1, m2 )<<"\n"<< endl;

    double maxval = 0, minval = 0;
    Point minloc, maxloc;
    minMaxLoc(m1, &minval, &maxval, &minloc, &maxloc);
    cout<< "minMaxLoc(m1, minval, maxval, minloc, maxloc)=\n "
        <<"minval=" << minval <<" maxval="<< maxval<<"\n"
        <<"minloc=" << minloc <<" maxloc="<< maxloc
        <<"\n"<<endl;

    transpose(m1, m3);
    cout <<"transpose( m1 )\n"<< m3 <<"\n"<< endl;

    invert(m1, m3 );
    cout <<"invert(m1, m3 )\n"<< m3 <<"\n"<< endl;

    vector<cv::Mat> marray{m1,m2};
    Mat dst;
    merge(marray, dst );
    cout <<"merge(marray, dst )\n"<< dst <<"\n"<< endl;

    transpose(dst, dst);
    cout <<"transpose(m1, dst)\n"<< dst <<"\n"<< endl;

    normalize(dst, dst, 0, 1, NORM_MINMAX );
    cout <<"normalize(m1, m3, 0, 1, NORM_MINMAX )\n"<< dst <<"\n"<< endl;

    flip(dst, dst, -1 );
    cout <<"flip(dst, dst )=\n"<< dst <<"\n"<< endl;

    gemm(dst ,dst, 10, dst,10, dst, GEMM_1_T);
    cout <<"gemm(dst ,dst, 10, dst,10, dst,GEMM_1_T )=\n"<< dst <<"\n"<< endl;

    dft(dst,dst );
    cout <<"dft(dst,dst )=\n"<< dst <<"\n"<< endl;

    idft(dst,dst );
    cout <<"idft(dst,dst )=\n"<< dst <<"\n"<< endl;

    split(dst, marray );
    cout <<"spilt(dst, marray )=\n"
        <<"marry[0] =\n " <<marray[0] <<"\n"
        << "marry[1] =\n " <<marray[1] <<"\n"
        <<"\n"<< endl;

    repeat(m1 ,1, 2,m3);
    cout <<"repeat(m1 , 1, 2 ,m3)=\n"<< m3 <<"\n"<< endl;

    int a = saturate_cast<int>( m1.at<float>(0,0 ) );
    int b = saturate_cast<int>( m1.at<float>(3,3 ) );
    cout <<"saturate_cast<int>(m1.at<float>(0,0)) =\n"<< a <<"\n"
         <<" m1.at<float>(3,3)) =\n"<< b
         << endl;
    return 0;
}
