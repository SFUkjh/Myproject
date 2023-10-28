#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取原始图像
    Mat srcImage = imread("OIP-D.jpg", IMREAD_COLOR);
    if (srcImage.empty())
    {
        cout << "Failed to read image" << endl;
        return -1;
    }
    int rawcols = srcImage.cols;
    // 创建高斯金字塔
    vector<Mat> pyramids;
    pyramids.push_back(srcImage);

    // 设置缩小的尺度因子
    float scale = 0.5;

    // 缩小图像直到宽度为原1/4
    while (srcImage.cols > rawcols/5 )
    {
        srcImage = pyramids.back();

        // 计算下一层金字塔的图像尺寸
        int dstWidth = srcImage.cols * scale;
        int dstHeight = srcImage.rows * scale;

        // 创建下一层金字塔图像
        Mat dstImage(dstHeight, dstWidth, srcImage.type());

        // 遍历目标图像的每个像素，并通过原始图像对应的位置进行赋值
        for (int i = 0; i < dstHeight; i++)
        {
            for (int j = 0; j < dstWidth; j++)
            {
                // 计算原始图像中对应像素的坐标
                int srcI = i / scale;
                int srcJ = j / scale;

                // 边界处理
                if (srcI >= srcImage.rows)
                    srcI = srcImage.rows - 1;
                if (srcJ >= srcImage.cols)
                    srcJ = srcImage.cols - 1;

                // 通过at函数获取对应位置的像素值，并赋值给目标图像
                dstImage.at<Vec3b>(i, j) = srcImage.at<Vec3b>(srcI, srcJ);
            }
        }

        // 将下一层金字塔图像保存到容器中
        pyramids.push_back(dstImage);
    }

    // 显示所有金字塔图像
    for (int i = 0; i < pyramids.size(); i++)
    {
        string windowName = "Pyramid Level " + to_string(i);
        namedWindow(windowName, WINDOW_AUTOSIZE);
        imshow(windowName, pyramids[i]);
        waitKey(100);
    }

    waitKey(0);

    return 0;
}