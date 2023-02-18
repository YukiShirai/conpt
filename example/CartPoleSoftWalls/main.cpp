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

#include "plot.hpp"

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

    // set initial and goal state
    Eigen::VectorXd xs = Eigen::VectorXd::Zero(4);
    Eigen::VectorXd xg = Eigen::VectorXd::Zero(4);

    xs << -0.152, 0, 0, 0;
    xg << 0.05, 0.12, 0, 0;

    conpt::CartPole ocp(param, xs, xg);
    
    cout << xg << endl;
    cout << "xg before opt" << endl;

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
    
    ocp.Q = Eigen::MatrixXd::Identity(4, 4);
    ocp.R = Eigen::MatrixXd::Identity(1, 1);
    // ocp.Q(1, 1) = 1;

    // ocp.R(0, 0) = 1;

    ocp.objective();

    ocp.init_const();

    // ocp.terminal_const();

    

    // setup initial state constraints
    // setup terminal state constraints

    const std::string solver{"ipopt"};

    cout << solver << endl;

    auto solution = ocp.run();


    conpt_plot::plot(solution, ocp);

    return 0;
}