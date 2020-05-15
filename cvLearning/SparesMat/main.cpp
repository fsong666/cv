#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main (){
	int size[] ={10, 10 };
	SparseMat sm(2 , size, CV_32F);

	for(int i = 0; i < 10 ; i++ ){
		int idx[2];
		idx[0] = size[0] * 2;
		idx[1] = size[1] * 3;

		sm.ref<float>(idx ) += 1.0f;
	}
	SparseMatConstIterator_<float> it = sm.begin<float>();
	SparseMatConstIterator_<float> it_end = sm.end<float>();

	for(; it != it_end ; it++ ){
		const SparseMat::Node* node = it.node();
		cout << node->idx[0]<<"\n"
			 <<node->idx[1] << "\n" 
			 <<*it << endl;
	}

	return 0;
}
