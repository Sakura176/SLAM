/***
 * @Author: 不摇碧莲
 * @Date: 2020-12-08 19:26:13
 * @LastEditTime: 2020-12-17 19:57:07
 * @LastEditors: 不摇碧莲
 * @Description: SLAM十四讲的基础知识练习
 * @FilePath: /SLAM十四讲/practice/question_1.cpp
 * @
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

/**
 * 题目１
 * 我们知道SLAM是处理序列图像的，有时候需要格式化的图像名字用作输入。
 * 前面提到的TUM的RGB-D数据集中图像是根据时间命名的，请从下面链接下载数据集fr1/desk
 * https://vision.in.tum.de/data/datasets/rgbd-dataset/download#并解压。
 * 请编程实现将文件夹/rgb下以时间命名的序列图片重新命名为0000-9999的格式。
 * 本程序学习目的：熟悉cmake的使用、OpenCV读写操作、C++的string操作
*/

int main(int argc, char const *argv[])
{
    // 目标文件夹路径
    string inPath = string(argv[1]);
    // 文件的存储路径
    string dest = string(argv[1]) + "/result/";
    // 记录图片的路径和文件名
    string saveFileName;
    // 容器，用于存储图片的名称
    vector<string> fileName;
    cv::Mat srcImg, dstImg;

    // 寻找与字符串匹配的文件路径
    cv::glob(inPath, fileName);
    for(int i=0; i<fileName.size(); ++i)
    {
        srcImg = cv::imread(fileName[i]);
        srcImg.copyTo(dstImg);
        if(i<10)
        {
            saveFileName = dest + "000" + to_string(i) + ".png";
            cv::imwrite(saveFileName, dstImg);
        }
        else if (i<99)
        {
            saveFileName = dest + "00" + to_string(i) + ".png";
            cv::imwrite(saveFileName, dstImg);
        }
        else if (i<999)
        {
            saveFileName = dest + "0" + to_string(i) + ".png";
            cv::imwrite(saveFileName, dstImg);
        }
        else if (i<9999)
        {
            saveFileName = dest + to_string(i) + ".png";
            cv::imwrite(saveFileName, dstImg);
        }
        cout << "成功处理第" << i << "张图片！！！" << endl;    
    }
    return 0;
}
