#pragma once
#include <iostream>
#include <Eigen/Core>
#include <vector>

using namespace std;

// get screw interpolation

/*
1. Given two 6d pose, start and goal
2. std::vector int num whose
*/

class interpolation
{
private:
    const int n_;

public:
    interpolation(int n, Eigen::Vector3d pos_s_, Eigen::Vector3d pos_g_, Eigen::Vector4d ori_s_, Eigen::Vector4d ori_g_);
    ~interpolation();

    Eigen::MatrixXd pos;
    Eigen::MatrixXd ori;

    Eigen::Vector3d pos_s;
    Eigen::Vector3d pos_g;

    Eigen::Vector4d ori_s;
    Eigen::Vector4d ori_g;

    void calcInterpolation();

    Eigen::Vector4d conj(Eigen::Vector4d quat);
    // TODO: better way should be operator overload with quat class
    Eigen::Vector4d product(Eigen::Vector4d q1, Eigen::Vector4d q2);

};

interpolation::interpolation(int n, Eigen::Vector3d pos_s_, Eigen::Vector3d pos_g_, Eigen::Vector4d ori_s_, Eigen::Vector4d ori_g_) : n_(n)
{
    pos = Eigen::MatrixXd::Zero(n + 2, 3);
    ori = Eigen::MatrixXd::Zero(n + 2, 4);

    pos_s = pos_s_;
    pos_g = pos_g_;
    ori_s = ori_s_;
    ori_g = ori_g_;

    pos.row(0) = pos_s_;
    pos.row(n + 2 - 1) = pos_g_;

    ori.row(0) = ori_s_;
    ori.row(n + 2 - 1) = ori_g_;
};

interpolation::~interpolation(){};

Eigen::Vector4d interpolation::conj(Eigen::Vector4d quat){
    Eigen::Vector4d conj_quat;

    conj_quat << quat(0), -quat(1), -quat(2), -quat(3);
    return conj_quat;
};

void interpolation::calcInterpolation()
{
    std::cout << "calcInterpolation is called!!" << std::endl;
    std::cout << "n_" << n_ << std::endl;
    // std::cout << "pos size " << pos << std::endl;
    // std::cout << "ori size " << ori << std::endl;
    double delta = 1.0 / (n_ + 1);

    cout << "delta" << delta << endl;

    for (size_t i = 0; i < n_ + 2; i++)
    {
        pos.row(i) = pos_s + i * delta * (pos_g - pos_s);
        ori.row(i) = interpolation::conj(ori_g);
    }
    std::cout << "pos" << std::endl;
    std::cout << pos << std::endl;

    std::cout << "ori" << std::endl;
    std::cout << ori << std::endl;
};

Eigen::Vector4d product(Eigen::Vector4d q1, Eigen::Vector4d q2){
    Eigen::Vector4d q3;

    q3(0) = q1(0) * q2(0) - q1(1) * q2(1) - q1(2) * q2(2) - q1(3) * q2(3);

};