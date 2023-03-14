#include <iostream>
#include <memory>
#include "Controller.hpp"

using namespace std;

int main()
{

    Eigen::Vector3d Kp = Eigen::Vector3d::Constant(1);
    Eigen::Vector3d Kd = Eigen::Vector3d::Zero();

    // Controller* cont;
    unique_ptr<stiffnessControl> pdcont;

    pdcont = make_unique<stiffnessControl>(3, 0.05, Kp, Kd);

    Eigen::VectorXd ref = Eigen::Vector3d::Constant(3);
    Eigen::VectorXd cur = Eigen::Vector3d::Zero();


    pdcont->calculateControl(ref, cur);
    

    // cout << "Kp: " << pdcont->Kp << endl;
    // cout << "Kd: " << pdcont.Kd << endl;

    // pdControl pdcont(3, Kp, Kd);

    // cout << "n: " << pdcont.num_joint << endl;
    // cout << "Kp: " << pdcont.Kp << endl;
    // cout << "Kd: " << pdcont.Kd << endl;
    return 0;
}