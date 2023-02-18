#ifndef _TO_BASE_H_
#define _TO_BASE_H_

#include <casadi/casadi.hpp>
#include <iostream>

// using namespace std;

namespace conpt
{

    class TO_base
    {
    private:
        casadi::MX x;
        casadi::MX u;
        casadi::MX y;
        casadi::MX xdot;
        casadi::Opti opti;

    public:
        TO_base(/* args */){std::cout << "constructor TO runs" << std::endl;};
        virtual ~TO_base(){};

        virtual void bounds() = 0;
        virtual void objective() = 0;
        virtual casadi::OptiSol run(const std::string &solver) = 0;
        // virtual void initialcondition(casadi::Opti &o, casadi::MX &x0) = 0;
        // virtual void bounds_finaltime(casadi::Opti &o, casadi::MX &xT) = 0;
        // virtual void constraint(casadi::Opti &o, casadi::MX &x, casadi::MX &xdot, casadi::MX &y, casadi::MX &u) = 0;
    };

} // end of namespace libContactRichOpt

#endif