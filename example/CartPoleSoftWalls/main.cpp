#include <iostream>
#include <param/param.hpp>
#include <casadi/casadi.hpp>
#include "conpt/CartPole.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <cmath>

#include <vector>

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


#include <Eigen/Core>
// #include <eigen3/Eigen/Core> if you don't specify Eigen3::Eigen in cmakelists.txt
// #include <Eigen/Core>

using namespace Eigen;

using namespace std;

int main()
{

    // // assume you are running from build directory.
    std::string filename = "param.cfg";

    char cwd[100000];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    param::parameter param(filename);
    if (!param)
    {
        std::cerr << "Could not find file " << filename << std::endl;
        std::abort();
    }

    // setup casadi class

    conpt::CartPole ocp(param);
    // cout << ocp.xb << endl;

    Eigen::MatrixXd xlb = Eigen::MatrixXd::Zero(1, ocp.nx);
    Eigen::MatrixXd xub = Eigen::MatrixXd::Zero(1, ocp.nx);

    Eigen::MatrixXd xdotlb = Eigen::MatrixXd::Zero(1, ocp.nx);
    Eigen::MatrixXd xdotub = Eigen::MatrixXd::Zero(1, ocp.nx);

    Eigen::MatrixXd ulb = Eigen::MatrixXd::Zero(1, ocp.nu);
    Eigen::MatrixXd uub = Eigen::MatrixXd::Zero(1, ocp.nu);

    Eigen::MatrixXd ylb = Eigen::MatrixXd::Zero(1, ocp.ny);
    Eigen::MatrixXd yub = Eigen::MatrixXd::Zero(1, ocp.ny);

    // cout << xlb.block<2, 2>(0, 1) << endl;

    xlb << -5, -2 * M_PI, -10, -10;
    xub << 5, 2 * M_PI, 10, 10;

    xdotlb << -10, -10, -100, -100;
    xdotub << 10, 10, 100, 100;

    ulb << -30;
    uub << 30;


    ylb << 0, 0, 0, 0, 0, 0, 0, 0;
    yub << 0.02, 0.02, 30, 30, 10, 10, 10, 50;


    ocp.xb.row(0) << xlb;
    ocp.xb.row(1) << xub;

    ocp.xdotb.row(0) << xdotlb;
    ocp.xdotb.row(1) << xdotub;

    ocp.ub.row(0) << ulb;
    ocp.ub.row(1) << uub;

    ocp.yb.row(0) << ylb;
    ocp.yb.row(1) << yub;



    ocp.bounds();


    // setup optimization parameters

    // ocp.Q << 0, 0, 0, 1;
    ocp.Q(1, 1) = 1;

    cout << ocp.Q << endl;
    cout << "R matrix is: " << endl;
    ocp.R(0, 0) = 1;

    cout << ocp.R << endl;

    ocp.objective();

    const std::string solver{"ipopt"};

    cout << solver << endl;

    ocp.run();
    // if you do not specify, it would use the default argument
    // ocp.run(solver);

    // ocp.opti.solver("ipopt");
    // auto sol = ocp.opti.solve();

    // cout << sol.value(ocp.x) << endl;



    // specify your bound value:
    // x
    // xdot
    // u
    // y
    

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
        plt::plot({1,3,2,4});
    plt::show();

    return 0;
}