#ifndef _PLOT_HPP_
#define _PLOT_HPP_
#include <casadi/casadi.hpp>
#include "conpt/CartPole.h"
#include <iostream>
#include <Eigen/Core>
using namespace Eigen;

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

using namespace std;

namespace conpt_plot
{

    void plot()
    {

        plt::plot({1, 3, 2, 4});
        plt::show();
    }

    std::vector<double> convert_array(casadi::OptiSol sol, casadi::MX x, int ind_var)
    {

        auto sol_x = sol.value(x);

        // cout << sol_x.size1() << ", " << sol_x.size2() << endl;
        // size 1 is num of row
        // size 2 is num of column

        Eigen::MatrixXd sol_x_2d = Eigen::MatrixXd::Zero(sol_x.size1(), sol_x.size2());

        auto sol_x_1d = static_cast<std::vector<double>>(sol_x);

        for (size_t i = 0; i < sol_x.size2(); i++)
        {
            for (size_t j = 0; j < sol_x.size1(); j++)
            {
                sol_x_2d(j, i) = sol_x_1d[(sol_x.size1()) * i + j];
            }
        }

        // cout << sol_x_2d << endl;

        std::vector<double> plot_x_2d;
        plot_x_2d.resize(sol_x_2d.col(0).size()); // resize the shape of the vector for given col vector
        VectorXd::Map(&plot_x_2d[0], sol_x_2d.col(0).size()) = sol_x_2d.col(ind_var);

        return plot_x_2d;
    }

    void plot(casadi::OptiSol sol, conpt::CartPole ocp)
    {

        // std::cout << "plot with conpt solution" << std::endl;
        // std::cout << "------------------------------" << std::endl;

        // auto sol_x = sol.value(ocp.x);

        // cout << sol_x.size1() << ", " << sol_x.size2() << endl;
        // // size 1 is num of row
        // // size 2 is num of column

        // Eigen::MatrixXd sol_x_2d = Eigen::MatrixXd::Zero(sol_x.size1(), sol_x.size2());

        // auto sol_x_1d = static_cast<std::vector<double>>(sol_x);

        // for (size_t i = 0; i < ocp.nx; i++)
        // {
        //     for (size_t j = 0; j < ocp.T+1; j++)
        //     {
        //         sol_x_2d(j, i) = sol_x_1d[(ocp.T+1)*i + j];
        //     }
        // }

        // cout << sol_x_2d << endl;

        // std::vector<double> plot_x_2d;
        // plot_x_2d.resize(sol_x_2d.col(0).size()); // resize the shape of the vector for given col vector
        // VectorXd::Map(&plot_x_2d[0], sol_x_2d.col(0).size()) = sol_x_2d.col(0);
        // // The goal is to copy value from Eigen to std::vector
        // // Map copies the value by doing the following steps:
        // // 1. get the memory of 1st argument, which is std vector
        // // 2. Given the memory of the 1st argument, create Eigen VectorXD with the size of the given 2nd argument
        // // 3. "=" operator is used to assign the value

        // // cout << plot_x_2d << endl;

        for (size_t i = 0; i < ocp.nx; i++)
        {
            plt::figure();
            auto plot_x_2d = convert_array(sol, ocp.x, i);
            plt::plot(plot_x_2d);
            plt::title("x" + std::to_string(i));
            plt::save("./x" + std::to_string(i) + ".png");
        }

        for (size_t i = 0; i < ocp.nu; i++)
        {
            plt::figure();
            auto plot_x_2d = convert_array(sol, ocp.u, i);
            plt::plot(plot_x_2d);
            plt::title("u" + std::to_string(i));
            plt::save("./u" + std::to_string(i) + ".png");
        }


        cout << "saved!" << endl;

    }
}

#endif