#include <iostream>
#include <param/param.hpp>
#include <casadi/casadi.hpp>
#include "conpt/CartPole.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <Eigen/Core>
// #include <eigen3/Eigen/Core> if you don't specify Eigen3::Eigen in cmakelists.txt
// #include <Eigen/Core>

using namespace Eigen;

using namespace std;

int main()
{

    // // assume you are running from build directory.
    // std::string filename = "param.cfg";

    // char cwd[100000];
    // if (getcwd(cwd, sizeof(cwd)) != NULL)
    // {
    //     printf("Current working dir: %s\n", cwd);
    // }
    // else
    // {
    //     perror("getcwd() error");
    //     return 1;
    // }
    // param::parameter param(filename);
    // if (!param)
    // {
    //     std::cerr << "Could not find file " << filename << std::endl;
    //     std::abort();
    // }

    // setup casadi class

    conpt::CartPole ocp;
    // ocp(para)
    // libContactRichOpt::CartPole ocp(param);
    // casadi::Opti opti;
    // casadi::MX x = opti.variable(ocp.T + 1, ocp.nx);
    // casadi::MX xdot = opti.variable(ocp.T + 1, ocp.nx);
    // casadi::MX u = opti.variable(ocp.T, ocp.nu);
    // casadi::MX y = opti.variable(ocp.T, ocp.ny);

    // cout << ocp.T << endl;

    // // setup bounds

    // // ocp.bounds(opti, x, xdot, u, y);

    // // cout << "Eigen Version: " << EIGEN_MAJOR_VERSION << "." 
    // // << EIGEN_MINOR_VERSION << endl;

    // MatrixXf A; // Matrix 3 by 3 with float
    // // Matrix3f B; // Matrix 4 by 4 with double

    // int xx= 10;

    // A = Eigen::MatrixXf::Zero(2,xx);
    // // B.setConstant(2);

    // // Matrix<short, 5, 5> M1;
    // // Matrix<float, 20, 75> M2;
    // // MatrixXf M3; // create unknown shape size of matrix with float

    // // M1.setZero();
    // // M3.setZero();

    // cout << A << endl;

    



    // cout << "LOAD CARTPOLE" << endl;


    // cout << c.T;
    // libContactRichOpt::CartPole *c = new libContactRichOpt::CartPole;

    return 0;
}