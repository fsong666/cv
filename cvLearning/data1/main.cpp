#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(){

	Point3i pa(10,5,1),pb(3,3,2);
	cout << "pa= " << pa.x << " " <<pa.y <<" "
	 << "pb= " << pb.x << " " <<pb.y
	 << " pa.pb=  "<< pa.dot( pb ) <<  endl;
	cout <<"pa cross pb=" << pa.cross( pb ).x <<","<<pa.cross( pb ).y<<","<<pa.cross( pb ).z
	 << endl;
    Point pp(10,5), pp2(20,20);
    Size sz(pp);//point2i to Size
    cout << "Size= " << sz.width << "," <<sz.height <<" ares=" <<sz.area()<<endl;

    //Rect
    Rect r(pp, sz), rb(pp, pp2) ;
    cout<<"Rect=" << r.x << "," <<r.y <<","
        << r.width << "," <<r.height << " ares="
        << r.area() <<" orgain="<< r.tl().x << "," <<r.tl().y
        << " Rect&= " << (r & rb).area()
       <<endl;

    //Scalar
    Scalar s(255,0,255 );//4 element vector
    cout <<"Scalar= "<< s[0] <<"," << s[1] << ","<< s[2]<< ","<<s[3] <<endl;

    //构建一个Mat（200*200）
    Mat image(200, 200, CV_8UC3, Scalar(0));
    //设置一个旋转矩形3个参数分别为：质心（矩形中心），矩形长宽100、50 旋转角度：30 （clockwise）
    //RotatedRect 函数返回一个旋转矩形对象
    RotatedRect rRect = RotatedRect(Point2f(100,100), Size2f(100,50), 30);

    Point2f vertices[4];      //定义4个点的数组
    rRect.points(vertices);   //将四个点存储到vertices数组中
    for (int i = 0; i < 4; i++)
        // 注意Scala中存储顺序 BGR
        line(image, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));
    // 返回外接矩形
    Rect brect = rRect.boundingRect();
    rectangle(image, brect, Scalar(255,0,0));
    imshow("rectangles", image);
    waitKey(0);

	return 0;
}
