#pragma once
#include <iostream>
#include <Eigen/Core>
#include <cmath>

using namespace std;

class threeR
{
private:
    double a1{0.2};
    double a2{0.1};

    double theta1{};
    double theta2{};

    Eigen::Vector3d theta = Eigen::Vector3d::Zero();
    Eigen::Vector3d pos = Eigen::Vector3d::Zero();
    Eigen::Matrix3d rot = Eigen::Matrix3d::Zero();

public:
    threeR();
    ~threeR();
    void FK(Eigen::Vector3d theta_);
    void IK(Eigen::Vector3d EE_);

    void Jacobian(Eigen::Vector3d qd_);
};

threeR::threeR()
{
}

threeR::~threeR()
{
}

void threeR::FK(Eigen::Vector3d theta_)
{
    Eigen::Matrix4d T_W2A = Eigen::Matrix4d::Zero();
    Eigen::Matrix4d T_A2B = Eigen::Matrix4d::Zero();
}

void threeR::IK(Eigen::Vector3d EE_)
{
    std::cout << "Hello IK" << endl;
    double x = EE_(0);
    double y = EE_(1);
    double th = EE_(2);
    double c2 = (pow(x, 2) + pow(y, 2) - pow(a1, 2) - pow(a2, 2)) / (2 * a1 * a2);
    double s2 = sqrt(1 - pow(c2, 2));
    double th2 = atan2(s2, c2);
    cout << th2 * (180 / M_PI) << endl;

    double k1 = a1 + a2 * c2;
    double k2 = a2 * s2;

    double th1 = atan2(y, x) - atan2(k2, k1);
    cout << th1 * (180 / M_PI) << endl;

    double th3 = th - th1 - th2;

    cout << th3 * (180 / M_PI) << endl;
};

void Jacobian(Eigen::Vector3d qd_){

    

};