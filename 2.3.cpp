#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/highgui/highgui_c.h>
#include<vector>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("OIP-D.jpg");
    pyrDown(img, img);
    imshow("1.src",img);
    //高斯模糊
    Mat Gauss_img;
    GaussianBlur(img, Gauss_img, Size(3, 3), 0, 0, BORDER_DEFAULT);
    imshow("2.gauss",Gauss_img);
    //转化灰度图
    Mat gray_img;
    cvtColor(Gauss_img, gray_img, COLOR_BGR2GRAY);
    imshow("3.gray",gray_img);
    //Sobel算子
    Mat Sobel_x, absX;
    Sobel(gray_img, Sobel_x, CV_16S, 1, 0);
    convertScaleAbs(Sobel_x, absX);
    imshow("4.Abs",absX);
    //二值化
    Mat thr_img;
    threshold(absX, thr_img, 0, 255, THRESH_OTSU);
    imshow("5.threshold",thr_img);

  //闭操作
    Mat element, mor_img;
    element = getStructuringElement(MORPH_RECT, Size(25,25));
    morphologyEx(thr_img, mor_img, MORPH_CLOSE, element);
    imshow("6.morphologyEx",mor_img);

    //膨胀、腐蚀
    Mat kernelX, kernelY, ker_img;
    kernelX = getStructuringElement(MORPH_RECT, Size(20, 1));
    kernelY = getStructuringElement(MORPH_RECT, Size(1, 19));

    dilate(mor_img, ker_img, kernelX);
    erode(ker_img, ker_img, kernelX);

    erode(ker_img, ker_img, kernelY);
    dilate(ker_img, ker_img, kernelY);
    imshow("7.dilate and erode",ker_img);

    //中值滤波
    Mat med_img;
    medianBlur(ker_img, med_img, 15);
    imshow("8.medianBlur",med_img);

    //查找轮廓
    vector<vector<Point>>contours;
    findContours(med_img, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
    drawContours(img,contours,-1, Scalar(0, 0, 255), 3);
    Mat roi_img;
    vector<Rect> boundRect(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        boundRect[i] = boundingRect(contours[i]);
        if (boundRect[i].width > boundRect[i].height * 2) //车牌尺寸判断
        {
            //在原图上绘制矩形
            rectangle(img, Rect(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height), Scalar(0, 255, 0), 2);
            imshow("原图", img); //ROI提取
            roi_img = img(Rect(boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height));
        }
    }
    imshow("10.ROI", roi_img);

    waitKey(0);
    return 0;
}