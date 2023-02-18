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

    // CartPole::CartPole(param::parameter &param) : TO_base(), nx(param.get<int>("nx")), ny(param.get<int>("ny")),
    //                                               nz(param.get<int>("nz")), nu(param.get<int>("nu"))
    // {
    //     std::cout << "constructor cartpole with param!" << std::endl;
    //     // auto bound_x = Eigen::MatrixXf::Zero(2,3);
    //     // std::cout << bound_x << std::endl;
    //     // bound_x = Eigen::MatrixXf::Zero(2,3);
    //     mc = param.get<double>("mc");
    //     g = param.get<double>("g");
    //     mp = param.get<double>("mp");
    //     l = param.get<double>("l");
    //     dt = param.get<double>("dt");
    //     k1 = param.get<double>("k1");
    //     k2 = param.get<double>("k2");

    //     T = param.get<int>("T");

    //     // setup casadi
    //     x = opti.variable(T + 1, nx);
    //     xdot = opti.variable(T + 1, nx);
    //     u = opti.variable(T, nu);
    //     y = opti.variable(T, ny);

    //     // for bounds
    //     xb = Eigen::MatrixXd::Zero(2, nx);
    //     xdotb = Eigen::MatrixXd::Zero(2, nx);
    //     ub = Eigen::MatrixXd::Zero(2, nu);
    //     yb = Eigen::MatrixXd::Zero(2, ny);

    //     // for optimization parameters
    //     Q = Eigen::MatrixXd::Zero(nx, nx);
    //     R = Eigen::MatrixXd::Zero(nu, nu);
    // }

    CartPole::CartPole(param::parameter &param, Eigen::VectorXd _xs, Eigen::VectorXd _xg) : TO_base(_xs, _xg), nx(param.get<int>("nx")), ny(param.get<int>("ny")),
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

        for (size_t j = 0; j < x.size1(); j++)
        {

            for (size_t i = 0; i < x.size2(); i++)
            {
                // you need to have opti.subject_to, to ensure constraints
                opti.subject_to(opti.bounded(xb(0, i), x(j, i), xb(1, i)));
                opti.subject_to(opti.bounded(xdotb(0, i), xdot(j, i), xdotb(1, i)));
            }
        }

        for (size_t j = 0; j < u.size1(); j++)
        {

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

        casadi::MX obj{0}; // this 0 initialization ensures that obj is scalar
        double sum{};

        for (size_t i = 1; i < T + 1; i++)
        {
            for (size_t j = 0; j < nx; j++)
            {
                // TODO: Assume that the matrix is diagonal...
                obj += (x(i, j) - xg(j)) * Q(j, j) * (x(i, j) - xg(j));
            }
        }

        for (size_t i = 0; i < T; i++)
        {
            for (size_t j = 0; j < nu; j++)
            {
                obj += (u(i, j)) * R(j, j) * (u(i, j));
            }
        }
        opti.minimize(obj);
    }

    void CartPole::init_const()
    {
        std::cout << "init const" << std::endl;
        for (size_t j = 0; j < nx; j++)
        {
            opti.subject_to(x(0, j) == xs(j));
        }
    }

    void CartPole::terminal_const()
    {
        std::cout << "terminal const" << std::endl;
        for (size_t j = 0; j < nx; j++)
        {
            opti.subject_to(x(T, j) == xg(j));
        }
    }

    casadi::OptiSol CartPole::run(const std::string &solver)
    {
        opti.solver(solver);
        casadi::OptiSol sol = opti.solve();

        return sol;
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