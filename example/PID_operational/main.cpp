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
3. consider PD control

*/

#include <iostream>
#include "twoR.hpp"
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

    // Eigen::Vector3d theta = Eigen::Vector3d::Zero();
    twoR robot;
    // robot.FK(theta);

    return 0;
}