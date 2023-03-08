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

public:
    twoR();
    ~twoR();
    void FK(Eigen::Vector3d theta_);
};

twoR::twoR()
{
    std::cout << "2R is called" << std::endl;
    std::cout << "a1 = " << a1 << std::endl;
    std::cout << "a2 = " << a2 << std::endl;
    std::cout << "pos = " << pos << std::endl;
}

twoR::~twoR()
{
}

void twoR::FK(Eigen::Vector3d theta_){
    std::cout << "FK is called" << std::endl;

    Eigen::Matrix4d T_W2A = Eigen::Matrix4d::Zero();
    Eigen::Matrix4d T_A2B = Eigen::Matrix4d::Zero();

    

}