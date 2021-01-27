#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <chrono>

/****************************************************
 * 本程序演示了如何使用2D-2D的特征匹配估计相机运动
 * **************************************************/

using namespace std;
using namespace cv;

void find_feature_matches(
    const Mat &img1, const Mat &img2,
    std::vector<KeyPoint> &kp1,
    std::vector<KeyPoint> &kp2,
    std::vector<DMatch> &matches);

void pose_estimation_2d2d(
    std::vector<KeyPoint> keypoints_1,
    std::vector<KeyPoint> keypoints_2,
    std::vector<DMatch> matches,
    Mat &R, Mat &t);

// 像素坐标转相机归一化坐标
Point2d pixel2cam(const Point2d &p, const Mat &K);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "usage: feature_extraction img1 img2" << endl;
        return 1;
    }

    Mat img1 = imread(argv[1], cv::IMREAD_COLOR);
    Mat img2 = imread(argv[2], cv::IMREAD_COLOR);
    assert(img1.data != nullptr && img2.data != nullptr);
    resize(img1, img1, Size(0, 0), 0.3, 0.3, INTER_AREA);
    resize(img2, img2, Size(0, 0), 0.3, 0.3, INTER_AREA);
    vector<KeyPoint> keypoint1, keypoint2;
    vector<DMatch> matches;

    find_feature_matches(img1, img2, keypoint1, keypoint2, matches);
    cout << "一共找到了" << matches.size() << "组匹配点" << endl;

    //-- 估计两张图像间运动
    Mat R, t;
    pose_estimation_2d2d(keypoint1, keypoint2, matches, R, t);

    //-- 验证E=t^R*scale
    Mat t_x =
        (Mat_<double>(3, 3) << 0, -t.at<double>(2, 0), t.at<double>(1, 0),
         t.at<double>(2, 0), 0, -t.at<double>(0, 0),
         -t.at<double>(1, 0), t.at<double>(0, 0), 0);
    cout << "t^R=" << endl
         << t_x * R << endl;

    //-- 验证对极约束
    Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    for (DMatch m : matches)
    {
        Point2d pt1 = pixel2cam(keypoint1[m.queryIdx].pt, K);
        Mat y1 = (Mat_<double>(3, 1) << pt1.x, pt1.y, 1);
        Point2d pt2 = pixel2cam(keypoint2[m.trainIdx].pt, K);
        Mat y2 = (Mat_<double>(3, 1) << pt2.x, pt2.y, 1);
        Mat d = y2.t() * t_x * R * y1;
        cout << "epipolar constraint = " << d << endl;
    }
    return 0;
}

void find_feature_matches(const Mat &img1, const Mat &img2,
                          std::vector<KeyPoint> &kp1, std::vector<KeyPoint> &kp2, std::vector<DMatch> &matches)
{
    //-- 初始化
    Mat descriptor_1, descriptor_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // -- 检测角点位置
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    detector->detect(img1, kp1);
    detector->detect(img2, kp2);

    // -- 计算描述子
    descriptor->compute(img1, kp1, descriptor_1);
    descriptor->compute(img2, kp2, descriptor_2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<douPoint2d pixel2cam(const Point2d &p, const Mat &K);
    //-- 特征点匹配
    t1 = chrono::steady_clock::now();
    matcher->match(descriptor_1, descriptor_2, matches);
    t2 = chrono::steady_clock::now();Point2d pixel2cam(const Point2d &p, const Mat &K);
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "match features  used " << time_used.count() << " second." << endl;
}

void pose_estimation_2d2d(std::vector<KeyPoint> keypoints_1, std::vector<KeyPoint> keypoints_2,
                          std::vector<DMatch> matches, Mat &R, Mat &t)
{
    // 相机内参
    Mat K = (Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    //-- 把匹配点转换为vector<Point2f>的形式
    vector<Point2f> points1;
    vector<Point2f> points2;

    for (int i = 0; i < (int)matches.size(); i++)
    {
        points1.push_back(keypoints_1[matches[i].queryIdx].pt);
        points2.push_back(keypoints_2[matches[i].trainIdx].pt);
    }

    //-- 计算基础矩阵
    Mat fundamental_matrix;
    fundamental_matrix = findFundamentalMat(points1, points2, cv::FM_8POINT);
    cout << "fundamental_matrix is " << endl
         << fundamental_matrix << endl;

    //-- 计算本质矩阵
    Point2d principal_point(325.1, 249.7); // 相机光心， TUM dataset标定值
    double focal_length = 521;             // 相机焦距， TUM dataset标定值
    Mat essential_matrix;
    essential_matrix = findEssentialMat(points1, points2, focal_length, principal_point);
    cout << "esssential_matrix is " << endl
         << essential_matrix << endl;

    //-- 计算单应矩阵
    //-- 但是本例中场景不是平面，单应矩阵意义不大
    Mat homography_matrix;
    homography_matrix = findHomography(points1, points2, RANSAC, 3);
    cout << "homography_matrix is " << endl
         << homography_matrix << endl;

    //-- 从本质矩阵中恢复旋转和平移信息
    recoverPose(essential_matrix, points1, points2, R, t, focal_length, principal_point);
    cout << "R is " << endl
         << R << endl;
    cout << "t is " << endl
         << t << endl;
}

// 像素坐标转相机归一化坐标
Point2d pixel2cam(const Point2d &p, const Mat &K)
{
    return Point2d
    (
      (p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
      (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
    );
}