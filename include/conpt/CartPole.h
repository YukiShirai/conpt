#ifndef _CARTPOLE_H_
#define _CARTPOLE_H_

#include "TO_base.h"
// #include <Eigen/Dense>
#include <vector>
#include <param/param.hpp>
#include <casadi/casadi.hpp>
#include <iostream>




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
        // param::parameter p();

    public:
        CartPole();
        // CartPole(param::parameter p);
        CartPole(param::parameter &param);
        // // CartPole(param::parameter param);
        //~CartPole();

        // void bounds(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) override;
        // void objective(casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) override;
        // void initialcondition(casadi::Opti &o, casadi::MX &x0) override;
        // void bounds_finaltime(casadi::Opti &o, casadi::MX &xT) override;
        // void constraint(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) override;
    };

} // end of namespace libContactRichOpt

#endif
