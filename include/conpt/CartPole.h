#ifndef _CARTPOLE_H_
#define _CARTPOLE_H_

#include "TO_base.h"
// #include <Eigen/Dense>
#include <vector>
#include <param/param.hpp>
#include <casadi/casadi.hpp>
#include <iostream>
#include <Eigen/Core>

using namespace Eigen;

namespace conpt
{

    class CartPole : public TO_base
    {
    public:
        double mc;
        double g;
        double mp;
        double l;
        double dt;
        double k1;
        double k2;

        // int T;
        // std::vector<double> times;

        const int nx;
        const int ny;
        const int nz;
        const int nu;
        const int nc;
        const int nlambda;

        casadi::MX x;
        casadi::MX u;
        casadi::MX lambda;
        casadi::MX y;
        casadi::MX xdot;
        casadi::Opti opti;

        // for bounds
        Eigen::MatrixXd xb;
        Eigen::MatrixXd xdotb;
        Eigen::MatrixXd lambdab;
        Eigen::MatrixXd ub;
        Eigen::MatrixXd yb;

        // for optimization matrix
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;

        // state dynamics
        Eigen::MatrixXd A;
        Eigen::MatrixXd B;
        Eigen::MatrixXd C;
        Eigen::VectorXd G;

        // LCP
        Eigen::MatrixXd D;
        Eigen::MatrixXd E;
        Eigen::MatrixXd F;
        Eigen::VectorXd H;

        int T;

        // casadi::Opti opti;
        // casadi::MX x;
        // casadi::MX xdot;
        // casadi::MX u;
        // casadi::MX y;

        // // for bounds
        // Eigen::MatrixXd xb;
        // Eigen::MatrixXd xdotb;
        // Eigen::MatrixXd ub;
        // Eigen::MatrixXd yb;

        // // for optimization matrix
        // Eigen::MatrixXd Q;
        // Eigen::MatrixXd R;

        // param::parameter p();

    public:
        CartPole();
        // CartPole(param::parameter p);
        // CartPole(param::parameter &param);
        CartPole(param::parameter &param, Eigen::VectorXd _xs, Eigen::VectorXd _xg);
        // // CartPole(param::parameter param);
        ~CartPole();

        void bounds() override;
        void objective() override;
        void init_const() override;
        void terminal_const() override;
        casadi::OptiSol run(const std::string &solver = "ipopt") override;

        void constraint() override;
        void constraint_cur(std::vector<casadi::MX> &x_, std::vector<casadi::MX> &xdot_, std::vector<casadi::MX> &u_, std::vector<casadi::MX> &lambda_, std::vector<casadi::MX> &y_);
        std::vector<casadi::MX> multiply(Eigen::MatrixXd A_, std::vector<casadi::MX> &B_);
    };

} // end of namespace libContactRichOpt

#endif
