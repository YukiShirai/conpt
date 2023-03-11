#pragma once
#include <iostream>
#include <Eigen/Core>

class twoR
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
    twoR();
    ~twoR();
    void FK(Eigen::Vector3d theta_);
};

twoR::twoR()
{
}

twoR::~twoR()
{
}

void twoR::FK(Eigen::Vector3d theta_){
    Eigen::Matrix4d T_W2A = Eigen::Matrix4d::Zero();
    Eigen::Matrix4d T_A2B = Eigen::Matrix4d::Zero();


}