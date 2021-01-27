/***
 * @Author: 不摇碧莲
 * @Date: 2020-12-17 19:23:54
 * @LastEditTime: 2020-12-17 20:54:01
 * @LastEditors: 不摇碧莲
 * @Description: 学习使用 DBoW3 库
 * @FilePath: /SLAM十四讲/ch11/feature_training.cpp
 * @
 */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <string>

#include "DBoW3/DBoW3.h"

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    // 读取图片
    cout << "reading image..." << endl;
    vector<Mat> images;
    for (int i = 0; i < 10; i++)
    {
        string path = "../data/" + to_string(i + 1) + ".png";
        images.push_back(imread(path));
    }
    // 提取ORB特征
    cout << "detecting ORB feature ... " << endl;
    Ptr<Feature2D> detector = ORB::create();
    vector<Mat> descriptors;
    for (Mat &image : images)
    {
        vector<KeyPoint> keypoints;
        Mat descriptor;
        detector->detectAndCompute(image, Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
    }

    // 创建词典
    cout << "creating vocabulary ... " << endl;
    DBoW3::Vocabulary vocab;
    vocab.create(descriptors);
    cout << "vocabulary info: " << vocab << endl;
    vocab.save("../vocabulary.yml.gz");
    cout << "done" << endl;

    return 0;

    return 0;
}
