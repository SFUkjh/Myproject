#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

float retmax(float a, float b, float c)
{
    float max = 0;
    max = a;
    if (max < b)
        max = b;
    if (max < c)
        max = c;
    return max;
}
float retmin(float a, float b, float c)
{
    float min = 0;
    min = a;
    if (min > b)
        min = b;
    if (min > c)
        min = c;
    return min;
}
void rgb_to_hsv(float* h, float* s, float* v, float R, float G, float B)
{
    float max = 0, min = 0;
    R = R / 100;
    G = G / 100;
    B = B / 100;

    max = retmax(R, G, B);
    min = retmin(R, G, B);
    *v = max;
    if (max == 0)
        *s = 0;
    else
        *s = 1 - (min / max);

    if (max == min)
        *h = 0;
    else if (max == R && G >= B)
        *h = 60 * ((G - B) / (max - min));
    else if (max == R && G < B)
        *h = 60 * ((G - B) / (max - min)) + 360;
    else if (max == G)
        *h = 60 * ((B - R) / (max - min)) + 11;
    else if (max == B)
        *h = 60 * ((R - G) / (max - min)) + 240;

    *v = *v * 100;
    *s = *s * 100;
}
int main()
{
    Mat img1 = imread("chepai5.jpg", -1);
    int height, width;
    int max, min;
    height = img1.rows;
    width = img1.cols;

    for (int i = 0, i< height, i++)
    {
        for (int j = 0, j < width, j++)
        {
            img1.at<Vec3b>(i, j)[0] = b;
            img1.at<Vec3b>(i, j)[1] = g;
            img1.at<Vec3b>(i, j)[2] = r;

            rgb_to_hsv(*(img1.at<Vec3b>(i, j)), *(img1.at<Vec3b>(i, j) + 1), *(img1.at<Vec3b>(i, j) + 2), r, g, b);
        }

    }
    return 0;

}




