/***
 * @Author: 不摇碧莲
 * @Date: 2020-12-09 11:14:52
 * @LastEditTime: 2020-12-09 18:05:12
 * @LastEditors: 不摇碧莲
 * @Description: 本程序学习目的：熟悉cmake的使用、学习eigen的基本操作；根据实践验证旋转矩阵的约束
 * @FilePath: /SLAM十四讲/practice/question_2.cpp
 * @
 */
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;
using namespace Eigen;

/**
 * 已知相机的位姿用四元数表示为q=[0.35,0.2,0.3,0.1],顺序为x,y,z,w，
 * 请编程实现：输出四元数对应的旋转矩阵、旋转矩阵的转置，旋转矩阵的逆矩阵，
 * 旋转矩阵乘以自身的转置，验证旋转矩阵的正交性。
 */

int main(int argc, char const *argv[])
{
    Quaterniond q = Quaterniond(0.1, 0.35, 0.2, 0.3);
    cout << "quaternion q = " << q.coeffs().transpose() << endl;
    Matrix3d m = q.matrix();
    cout << "Matrix3d from quaternion q = " << endl << m << endl;
    Matrix3d m_tranpose = m.transpose();
    cout << "tranpose of Matrix3d = " << endl << m_tranpose << endl;
    Matrix3d m_inverse = m.inverse();
    cout << "inverse of Matrix3d = " << endl << m_inverse << endl;
    Matrix3d m_cal = m * m.transpose();
    cout << "m_cal of Matrix3d = " << endl << m_cal << endl;
    return 0;
}
