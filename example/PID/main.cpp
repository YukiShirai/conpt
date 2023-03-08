#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "User.cpp"
#include <string>
#include "PID.cpp"
#include "matplotlibcpp.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>


namespace plt = matplotlibcpp;

using namespace std;

int main()
{
    srand(time(0)); // Seed the random number generator with the current time
    double min_value = -2.0;
    double max_value = 2.0;
    int precision = 2;

    PID pid = PID(0.1, 100, -100, 0.5, 0.05, 0.);

    double val = 20;
    double target = 0;

    int trial{100};

    std::vector<double> result;
    std::vector<double> ref;
    result.push_back(val);

    for (int i = 0; i < trial; i++)
    {
        double random_number = min_value + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max_value - min_value)));
        std::cout <<  random_number << std::endl;
        // std::cout << std::fixed << std::setprecision(precision) << random_number << std::endl;

        double inc = pid.calculate(target, val);
        // printf("val:% 7.3f inc:% 7.3f\n", val, inc);
        val += inc + random_number;
        result.push_back(val);
        ref.push_back(target);
    }

    plt::figure();
    plt::plot(result);
    plt::plot(ref);
    plt::show();

    return 0;
}