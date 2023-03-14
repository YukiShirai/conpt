// the goal is to control the end effector position. I need to do
// Input: time history of joint angle and its velocity
// output: figure
/*
- Controller: PID
- Simulation: forward dynamics, forward kinematics
- Ik
- Jacobian
*/

/*
Goal: in operational space, achieve impedance control given reference 6D trajectory for 2R arm with wrench profile
Tasks:
- kinematics
- propagation of equation
Logic:
1. Given two pose, calculate the interpolation
2. calculate the desired torque using inverse dynamics
3. consider PD control in joint space, then operational space, then PD with stiffness in joint space, and then in operational space

*/

#include <iostream>
#include "threeR.hpp"
#include "interpolation.hpp"
#include <Eigen/Dense>

using namespace std;

int main()
{

    cout << "Hello PID operational space" << endl;

    int n = 5;

    Eigen::Vector3d pos_s_ = Eigen::Vector3d::Zero();
    pos_s_ << 0.1, 0.05, 0;
    Eigen::Vector3d pos_g_;
    pos_g_ << 0.1, 0.1, 0;

    double yaw_s = M_PI / 6.0; // 30 degrees
    double yaw_g = M_PI / 4.0; // 45 degrees

    Eigen::Matrix3d ori_s_;
    ori_s_ = Eigen::AngleAxisd(yaw_s, Eigen::Vector3d::UnitZ());

    Eigen::Matrix3d ori_g_;
    ori_g_ = Eigen::AngleAxisd(yaw_g, Eigen::Vector3d::UnitZ());

    interpolation inter(n, pos_s_, pos_g_, ori_s_, ori_g_);

    inter.calcInterpolation();

    auto posInterpolation = inter.pos;
    auto rotInterpolation = inter.ori;

    // convert 3d position and rotation matrix to 3d vector
    list<Eigen::Vector3d>::iterator it;
    list<Eigen::Matrix3d>::iterator it2;

    list<Eigen::Vector3d> EE;

    for (it = posInterpolation.begin(), it2 = rotInterpolation.begin(); it != posInterpolation.end(); it++, it2++)
    {
        Eigen::Vector3d temp = Eigen::Vector3d::Zero();
        temp(0) = (*it)(0);
        temp(1) = (*it)(1);
        temp(2) = atan2((*it2)(1, 0), (*it2)(0, 0));
        EE.push_back(temp);
    }

    threeR robot;
    list<Eigen::Vector3d>::iterator it_ik;

    for (it_ik = EE.begin(); it_ik != EE.end(); it_ik++)
    {
        auto temp = robot.IK(*it_ik);
    }

    // implement controller:

    return 0;
}