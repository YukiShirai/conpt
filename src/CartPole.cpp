#include "../include/conpt/CartPole.h"

#include <Eigen/Dense>
#include <param/param.hpp>
#include <iostream>
#include <Eigen/Core>
#include <casadi/casadi.hpp>


using namespace Eigen;
using namespace casadi;
using namespace std;

namespace conpt
{

    CartPole::CartPole() : TO_base(), nx(0), ny(0), nz(0), nu(0)
    {
        std::cout << "constructor cartpole  no input for now with python!!!" << std::endl;
        // auto bound_x = Eigen::MatrixXf::Zero(2,3);
    }

    CartPole::CartPole(param::parameter &param) : TO_base(), nx(param.get<int>("nx")), ny(param.get<int>("ny")), 
    nz(param.get<int>("nz")), nu(param.get<int>("nu"))
    {
        std::cout << "constructor cartpole with param!" << std::endl;
        // auto bound_x = Eigen::MatrixXf::Zero(2,3);
        // std::cout << bound_x << std::endl;
        // bound_x = Eigen::MatrixXf::Zero(2,3);
        mc = param.get<double>("mc");
        g = param.get<double>("g");
        mp = param.get<double>("mp");
        l = param.get<double>("l");
        dt = param.get<double>("dt");
        k1 = param.get<double>("k1");
        k2 = param.get<double>("k2");

        T = param.get<int>("T");

        // const int nx = param.get<int>("nx");
        // const int ny = param.get<int>("ny");
        // const int nz = param.get<int>("nz");
        // const int nu = param.get<int>("nu");


        // setup casadi
        x = opti.variable(T + 1, nx);
        xdot = opti.variable(T + 1, nx);
        u = opti.variable(T, nu);
        y = opti.variable(T, ny);

        // for bounds
        xb = Eigen::MatrixXd::Zero(2, nx);
        xdotb = Eigen::MatrixXd::Zero(2, nx);
        ub = Eigen::MatrixXd::Zero(2, nu);
        yb = Eigen::MatrixXd::Zero(2, ny);

        // for optimization parameters
        Q = Eigen::MatrixXd::Zero(nx, nx);
        R = Eigen::MatrixXd::Zero(nu, nu);


    }

    CartPole::~CartPole()
    {
    }

    void CartPole::bounds()
    {
        std::cout << "bound" << std::endl;

        for (size_t j = 0; j < x.size1(); j++){

            for (size_t i = 0; i < x.size2(); i++)
            {
                // you need to have opti.subject_to, to ensure constraints
                opti.subject_to(opti.bounded(xb(0, i), x(j, i), xb(1, i)));
                opti.subject_to(opti.bounded(xdotb(0, i), xdot(j, i), xdotb(1, i)));
            }

        }

        for (size_t j = 0; j < u.size1(); j++){

            for (size_t i = 0; i < u.size2(); i++)
            {
                // Assumption: time horizon of u and y are same
                opti.subject_to(opti.bounded(ub(0, i), u(j, i), ub(1, i)));
                opti.subject_to(opti.bounded(yb(0, i), y(j, i), yb(1, i)));
            }

        }
        

    }

// TODO: We should have terminal objective as well
    void CartPole::objective()
    {
        std::cout << "obj" << std::endl;

        casadi::MX obj{};
        double sum{};

        // cout << obj << endl;

        // for (size_t j = 0; j < u.size1(); j++){

        //     // obj(0) += 1;
        //     sum += 1;

        // }

        // cout << sum << endl;


        // opti.minimize(sum);
        // opti.minimize(-(x(0, 0) +0.2)* (x(0, 0) +0.2));
        opti.minimize(pow(x(0, 0)-1, 2)+pow(x(1, 0)-2, 2)+pow(x(0, 1)+3, 2));
        // std::cout << pow(x(0, 0), 2) << std::endl;
    }
    casadi::OptiSol CartPole::run(const std::string &solver)
    {
        opti.solver(solver);
        casadi::OptiSol sol = opti.solve();
    //         std::cout << "Original conpt solution" << std::endl;
    // std::cout << "------------------------------" << std::endl;
    //     cout << sol.value(x) << endl;

        return sol;
        // cout << "here we use value variable --" << endl;
        // cout << sol.value_variables() << endl;
    }

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