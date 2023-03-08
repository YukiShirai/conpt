#ifndef _PID_CPP_
#define _PID_CPP_

#include <iostream>
#include <cmath>
#include "PID.h"
/*This code is originally from here: https://gist.github.com/bradley219/5373998*/

class PID::Impl
{
private:
    double _dt;
    double _max;
    double _min;
    double _Kp;
    double _Ki;
    double _Kd;
    double _pre_error;
    double _integral;

public:
    Impl(double dt, double max, double min, double Kp, double Kd, double Ki);
    ~Impl();
    double calc_implementation(double setpoint, double pv);
};

// Implementation
PID::Impl::Impl(double dt, double max, double min, double Kp, double Kd, double Ki) : _dt(dt),
                                                                                      _max(max),
                                                                                      _min(min),
                                                                                      _Kp(Kp),
                                                                                      _Kd(Kd),
                                                                                      _Ki(Ki),
                                                                                      _pre_error(0),
                                                                                      _integral(0){

                                                                                      };

PID::Impl::~Impl() = default;

double PID::Impl::calc_implementation(double setpoint, double pv)
{
    // calculate P error
    double error = setpoint - pv;
    double Pout = _Kp * error;

    // calculate I error

    _integral += error * _dt;

    double Iout = _Ki * _integral;

    // calculate D error

    double derivative = (error - _pre_error) / _dt;
    double Dout = _Kd * derivative;

    double output = Pout + Iout + Dout;

    // saturation

    if (output> _max)
    {
        output = _max;
    }
    else if(output < _min)
    {
    output = _min;
    }
    



    // update pre_error
    _pre_error = error;
    return output;
};

// API

PID::PID(double dt, double max, double min, double Kp, double Kd, double Ki):pimpl(new Impl(dt, max, min, Kp, Kd, Ki))
{
};

PID::~PID(){

};
double PID::calculate(double setpoint, double pv){
    double op = pimpl->calc_implementation(setpoint, pv);
    return op;
};

#endif