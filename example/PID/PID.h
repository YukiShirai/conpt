#ifndef _PID_H_
#define _PID_H_
#include <iostream>
#include <memory>

class PID
{
private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
    /* data */
public:
    PID(double dt, double max, double min, double Kp, double Kd, double Ki);
    ~PID();

    // make the function public which is API
    double calculate(double setpoint, double pv);


};

#endif