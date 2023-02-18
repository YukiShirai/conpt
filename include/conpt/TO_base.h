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
        virtual void init_const() = 0;
        virtual void terminal_const() = 0;
        
        // virtual void constraint() = 0;

        // initial and terminal values
        Eigen::VectorXd xs;
        Eigen::VectorXd xg;
    };

} // end of namespace libContactRichOpt

#endif