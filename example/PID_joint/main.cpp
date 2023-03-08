// the goal is to control the end effector position. I need to do
// Input: time history of joint angle and its velocity
// output: figure
/*
- Controller: PID
- Simulation: forward dynamics, forward kinematics
- Ik
- Jacobian
*/
#include <iostream>
#include "twoR.hpp"



using namespace std;

int main(){

    cout << "Hello PID joint space" << endl;

    twoR robot;

    Eigen::Vector3d theta = Eigen::Vector3d::Zero();

    robot.FK(theta);

    return 0;
}