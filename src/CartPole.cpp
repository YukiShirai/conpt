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

    CartPole::CartPole() : TO_base(), nx(0), ny(0), nz(0), nu(0), nc(0), nlambda(0)
    {
        std::cout << "constructor cartpole no input for now with python!" << std::endl;
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
                                                                                            nz(param.get<int>("nz")), nu(param.get<int>("nu")), nc(param.get<int>("nc")), nlambda(param.get<int>("nlambda"))
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
        lambda = opti.variable(T, nlambda);
        y = opti.variable(T, ny);

        // for bounds
        xb = Eigen::MatrixXd::Zero(2, nx);
        xdotb = Eigen::MatrixXd::Zero(2, nx);
        ub = Eigen::MatrixXd::Zero(2, nu);
        lambdab = Eigen::MatrixXd::Zero(2, nlambda);
        yb = Eigen::MatrixXd::Zero(2, ny);

        // for optimization parameters
        Q = Eigen::MatrixXd::Zero(nx, nx);
        R = Eigen::MatrixXd::Zero(nu, nu);

        // setup dynamics constraints

        A = Eigen::MatrixXd::Zero(nx, nx);
        B = Eigen::MatrixXd::Zero(nx, nu);
        C = Eigen::MatrixXd::Zero(nx, nc);
        G = Eigen::VectorXd::Zero(nx);

        D = Eigen::MatrixXd::Zero(nc, nx);
        E = Eigen::MatrixXd::Zero(nc, nu);
        F = Eigen::MatrixXd::Zero(nc, nc);
        H = Eigen::VectorXd::Zero(nc);

        A.row(0) << 0, 0, 1, 0;
        A.row(1) << 0, 0, 0, 1;
        A.row(2) << 0, g * mp / mc, 0, 0;
        A.row(3) << 0, g * (mc + mp) / (l * mc), 0, 0;

        // B.row(0) << 0, 0, 1 / mc, 1 / (l * mc);
        B.row(0) << 0;
        B.row(1) << 0;
        B.row(2) << 1 / mc;
        B.row(3) << 1 / (l * mc);

        C.row(0) << 0, 0;
        C.row(1) << 0, 0;
        C.row(2) << 0, 0;
        C.row(3) << 1 / (l * mp), -1 / (l * mp);
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
            }
        }

        for (size_t j = 0; j < lambda.size1(); j++)
        {

            for (size_t i = 0; i < lambda.size2(); i++)
            {
                opti.subject_to(opti.bounded(lambdab(0, i), lambda(j, i), lambdab(1, i)));
            }
        }

        for (size_t j = 0; j < y.size1(); j++)
        {
            for (size_t i = 0; i < y.size2(); i++)
            {
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

    void CartPole::constraint()
    {
        std::cout << "constraint" << std::endl;

        // for (size_t i = 0; i < T; i++)
        // {
        //     auto dx = A * x.row(i);
        // }
        // auto dx = A * casadi::transpose(x.row(0));
        // auto dx = A * x.row(0);
        // cout << "dx!!" << endl;

        for (size_t i = 0; i < T; i++)
        {

            // setup vector for each timestep
            std::vector<casadi::MX> temp_x;
            std::vector<casadi::MX> temp_x_next;
            std::vector<casadi::MX> temp_xdot;
            std::vector<casadi::MX> temp_u;
            std::vector<casadi::MX> temp_y;
            std::vector<casadi::MX> temp_lambda;
            for (size_t j = 0; j < nx; j++)
            {
                temp_x.push_back(x(i, j));
                temp_xdot.push_back(xdot(i, j));
                temp_x_next.push_back(x(i + 1, j)); // next time step!
            }
            for (size_t j = 0; j < nu; j++)
            {
                temp_u.push_back(u(i, j));
            }
            for (size_t j = 0; j < nlambda; j++)
            {
                temp_lambda.push_back(lambda(i, j));
            }
            for (size_t j = 0; j < ny; j++)
            {
                temp_y.push_back(y(i, j));
            }

            constraint_cur(temp_x, temp_xdot, temp_u, temp_lambda, temp_y);

            for (size_t j = 0; j < nx; j++)
            {
                opti.subject_to(temp_x_next[j] - temp_x[j] == temp_xdot[j] * dt);
            }
            

            // opti.subject_to()

            // auto temp = multiply(A, temp_x);
        }
    }

    casadi::OptiSol CartPole::run(const std::string &solver)
    {
        opti.solver(solver);
        casadi::OptiSol sol = opti.solve();

        return sol;
    }

    void CartPole::constraint_cur(std::vector<casadi::MX> &x_, std::vector<casadi::MX> &xdot_, std::vector<casadi::MX> &u_, std::vector<casadi::MX> &lambda_, std::vector<casadi::MX> &y_)
    {
        std::vector<casadi::MX> Ax;
        std::vector<casadi::MX> Bu;
        std::vector<casadi::MX> Clambda;
        std::vector<casadi::MX> Gg;

        Ax = multiply(A, x_);
        Bu = multiply(B, u_);
        Clambda = multiply(C, lambda_);

        // state dynamics constraints:

        for (size_t i = 0; i < nx; i++)
        {
            opti.subject_to(xdot_[i] == Ax[i] + Bu[i] + Clambda[i]);
        }

    }

    std::vector<casadi::MX> CartPole::multiply(Eigen::MatrixXd A_, std::vector<casadi::MX> &x_)
    {
        std::vector<casadi::MX> Ax;

        int C1 = A_.cols();
        int R1 = A_.rows();
        int R2 = x_.size();
        // cout << " A_ size " << C1 << ", " << R1 << endl;
        // cout << " B size " << R2 << endl;

        // check the size of matrix
        if (C1 != R2)
        {
            printf("The number of columns in Matrix-1  must be "
                   "equal to the number of rows in "
                   "Matrix-2\n");
            printf("Please update MACROs value according to "
                   "your array dimension in "
                   "#define section\n");

            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < A_.rows(); i++)
        {
            casadi::MX sum{0};
            for (size_t j = 0; j < 1; j++) // assume that x is n by 1 matrix
            {
                for (size_t k = 0; k < A_.cols(); k++)
                {
                    sum += A_(i, k) * x_[k];
                }
                
                Ax.push_back(sum);
            }
        }

        return Ax;
    }


} 