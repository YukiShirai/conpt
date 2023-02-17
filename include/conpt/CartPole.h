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

        int T;
        // std::vector<double> times;

        int nx;
        int ny;
        int nz;
        int nu;

        casadi::Opti opti;
        casadi::MX x;
        casadi::MX xdot;
        casadi::MX u;
        casadi::MX y;

        // for bounds
        Eigen::MatrixXd xb;
        Eigen::MatrixXd xdotb;
        Eigen::MatrixXd ub;
        Eigen::MatrixXd yb;

        // for optimization matrix
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;

        // param::parameter p();

    public:
        CartPole();
        // CartPole(param::parameter p);
        CartPole(param::parameter &param);
        // // CartPole(param::parameter param);
        ~CartPole();

        void bounds() override;
        void objective() override;
        void run(const std::string &solver = "ipopt") override;
        // void initialcondition(casadi::Opti &o, casadi::MX &x0) override;
        // void bounds_finaltime(casadi::Opti &o, casadi::MX &xT) override;
        // void constraint(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) override;
    };

} // end of namespace libContactRichOpt

#endif
