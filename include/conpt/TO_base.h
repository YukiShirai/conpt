#ifndef _TO_BASE_H_
#define _TO_BASE_H_

#include <casadi/casadi.hpp>
#include <iostream>
#include <Eigen/Core>
// using namespace std;

namespace conpt
{

    class TO_base
    {
    public:
        // casadi::MX x;
        // casadi::MX u;
        // casadi::MX y;
        // casadi::MX xdot;
        // casadi::Opti opti;

        //         // for bounds
        // Eigen::MatrixXd xb;
        // Eigen::MatrixXd xdotb;
        // Eigen::MatrixXd ub;
        // Eigen::MatrixXd yb;

        // // for optimization matrix
        // Eigen::MatrixXd Q;
        // Eigen::MatrixXd R;

        // int T;

    public:
        TO_base(/* args */) { std::cout << "constructor TO runs" << std::endl; };

        TO_base(Eigen::VectorXd _xs, Eigen::VectorXd _xg): xs(_xs), xg(_xg) {std::cout << "base constructor with specified xs and xg." << std::endl; };
        virtual ~TO_base(){};

        virtual void bounds() = 0;
        virtual void objective() = 0;
        virtual casadi::OptiSol run(const std::string &solver) = 0;
        // virtual void initialcondition(casadi::Opti &o, casadi::MX &x0) = 0;
        // virtual void bounds_finaltime(casadi::Opti &o, casadi::MX &xT) = 0;
        // virtual void constraint(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) = 0;

        // initial and terminal values
        Eigen::VectorXd xs;
        Eigen::VectorXd xg;
    };

} // end of namespace libContactRichOpt

#endif