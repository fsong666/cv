#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

template <typename T > void print(T &m ){
	cout <<"m= " <<endl;

	for(int j = 0; j < 3; j++ ){
		for(int k = 0 ; k < 3; k++)
			cout<<m(j,k)<<" ";
		cout<<endl;
	}
	cout << endl;
}

int main(){
	Matx33f m,m1 = cv::Matx33f::eye();
	Matx33f  m2 = cv::Matx33f::randu(0, 9 );
	cout << m1 <<endl;
	print(m1);
	print(m2);		
	m =m1 + m2;
	print(m );
	m =m1 * m2;
	print(m );
	cout << m1.dot(m2)<<endl;
	cout << "t()= "<<m2.t()<<'\n'<<endl;
	cout << "1.row=" << m2.row(1) << '\n'<< endl;
	cout << "inv=" << m2.inv(DECOMP_LU) <<'\n' << endl;

	//complex
	Complexf z(2 ,2);
	cout << "z= " << z<<endl;
	cout << "z2= " << z.conj() <<endl;
	return 0;
}

