#include "../include/conpt/CartPole.h"

#include <Eigen/Dense>
#include <param/param.hpp>
#include <iostream>
#include <Eigen/Core>

using namespace Eigen;
// using namespace std;

namespace conpt
{

    CartPole::CartPole() : TO_base()
    {
        std::cout << "constructor cartpole  no input for now!!!" << std::endl;
    }

    CartPole::CartPole(param::parameter &param) : TO_base()
    {
        std::cout << "constructor cartpole" << std::endl;
        // mc = param.get<double>("mc");
        // g = param.get<double>("g");
        // mp = param.get<double>("mp");
        // l = param.get<double>("l");
        // dt = param.get<double>("dt");
        // k1 = param.get<double>("k1");
        // k2 = param.get<double>("k2");

        // // T = param.get<int>("T");

        // nx = param.get<int>("nx");
        // ny = param.get<int>("ny");
        // nz = param.get<int>("nz");
        // nu = param.get<int>("nu");
        // cout << "constructor cartpole" << endl;
    }

    // CartPole::~CartPole()
    // {
    // }

    // void CartPole::bounds(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u)
    // {
    //             cout << "print" << endl;
    //     // Eigen::MatrixXf bound_x;
    //     // bound_x = Eigen::MatrixXf::Zero(2,3);


    //     // // Eigen::VectorXf lb_x(nx);
    //     // // bound_x.setZero();
    //     // cout << bound_x << endl;
    //     cout << "print" << endl;
    //     for (int i = 0; i < T+1; i++) // only for x and xdot
    //     {
    //         // cout << x(i, 0) << endl;
    //         // Eigen::Array<casadi::MX, 2, 1> X{x(i, 0), x(i, 0)};
    //         // cout << X << endl;
    //     }
        
    // }

    // void CartPole::objective(casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u)
    // {
    // }

    // void CartPole::initialcondition(casadi::Opti &o, casadi::MX &x0)
    // {
    // }

    // void CartPole::bounds_finaltime(casadi::Opti &o, casadi::MX &xT)
    // {
    // }

    // void CartPole::constraint(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u)
    // {
    // }


} // end of namespace libContactRichOpt