#pragma once
#include <iostream>
#include <Eigen/Core>
#include <list>
#include <unsupported/Eigen/MatrixFunctions>

using namespace std;

template <typename T>
void showlist(list<T> g)
{
    typename list<T>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout  << *it << endl;
    cout << '\n';
};


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
    interpolation(int n, Eigen::Vector3d pos_s_, Eigen::Vector3d pos_g_, Eigen::Matrix3d ori_s_, Eigen::Matrix3d ori_g_);
    ~interpolation();

    std::list<Eigen::Vector3d> pos;
    std::list<Eigen::Matrix3d> ori;

    Eigen::Vector3d pos_s;
    Eigen::Vector3d pos_g;

    Eigen::Matrix3d ori_s;
    Eigen::Matrix3d ori_g;

    void calcInterpolation();

    // Eigen::Vector4d conj(Eigen::Vector4d quat);
    // // TODO: better way should be operator overload with quat class
    // Eigen::Vector4d product(Eigen::Vector4d q1, Eigen::Vector4d q2);

};

interpolation::interpolation(int n, Eigen::Vector3d pos_s_, Eigen::Vector3d pos_g_, Eigen::Matrix3d ori_s_, Eigen::Matrix3d ori_g_) : n_(n)
{
    // pos = Eigen::MatrixXd::Zero(n + 2, 3);
    // // ori = Eigen::MatrixXd::Zero(n + 2, 3, 3);

    pos_s = pos_s_;
    pos_g = pos_g_;
    ori_s = ori_s_;
    ori_g = ori_g_;


};

interpolation::~interpolation(){};



void interpolation::calcInterpolation()
{
    std::cout << "calcInterpolation is called!!" << std::endl;

    double delta = 1.0 / (n_ + 1);

    // cout << "expo" << ori_s.exp() << endl;

    for (size_t i = 0; i < n_ + 2; i++)
    {
        pos.push_back(pos_s + i * delta * (pos_g - pos_s));
        auto log_matrix = (ori_g * ori_s.inverse()).log();
        auto temp = (log_matrix * i * delta).exp() * ori_s;
        ori.push_back(temp);
    }
    // showlist(pos);
    // showlist(ori);

};


