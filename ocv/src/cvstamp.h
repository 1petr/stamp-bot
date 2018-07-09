#ifndef CVFUCTIONS_H
#define CVFUCTIONS_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

class cvStamp
{

private:

    string pathImage;
    Mat image;
    Mat imageCircles;
    Mat imageRoi;
    Mat imageClasters;
    Mat imageBlue;
    Mat *img;
    Rect *rois;

public:

    cvStamp();
	cvStamp(string path);
    ~cvStamp();

    Mat getImage();
	void setSizeRotate(float sz);
    bool setRoi(Mat &img);
    void setImageToCircle();
    void setImageToBlue();
    Mat setClasters(Mat &img, int _shag);
    int orientationMap(const cv::Mat& img, int c);

	void showImage(string im_path);
    void showImageAll();

	void saveImage(string _pathImage,  Mat img);
    

};

#endif // CVSTAMP_H
