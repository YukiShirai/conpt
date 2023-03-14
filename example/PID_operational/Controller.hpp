/*
Set up abstract class for controller:
1. set gains
2. calculate control action given reference
3. PD control in joint space
*/

#include <iostream>
#include <cmath>
#include <Eigen/Core>

using namespace std;
// ////////////////////////////////////////////////
class Controller
{

public:
    Controller(int n_, double dt_);
    virtual ~Controller();
    virtual void calculateControl(Eigen::VectorXd &ref, Eigen::VectorXd &cur) = 0;

public:
    int num_joint;
    double dt;
    Eigen::VectorXd u;
    
};

Controller::Controller(int n_, double dt_) : num_joint(n_), dt(dt_), u(Eigen::VectorXd::Zero(n_))
{
    cout << "\033[1;31mBase class of the controller is called\033[0m\n";
};

Controller::~Controller()
{
    cout << "\033[1;31mBase class of the controller is deleted\033[0m\n";
};

// ////////////////////////////////////////////////

class pdControl : public Controller
{
public:
    Eigen::VectorXd Kp;
    Eigen::VectorXd Kd;

public:
    pdControl(int n_, double dt_, Eigen::VectorXd Kp_, Eigen::VectorXd Kd_);
    virtual ~pdControl() { cout << "\033[1;34mPD controller is deleted\033[0m\n"; };
    virtual void calculateControl(Eigen::VectorXd &ref, Eigen::VectorXd &cur) override;
};

pdControl::pdControl(int n_, double dt_, Eigen::VectorXd Kp_, Eigen::VectorXd Kd_) : Controller(n_, dt_), Kp(Kp_), Kd(Kd_)
{
    cout << "\033[1;34mPD controller is defined\033[0m\n";
};
void pdControl::calculateControl(Eigen::VectorXd &ref, Eigen::VectorXd &cur)
{
    cout << "calc pd control..." << endl;
    for (int i = 0; i < num_joint; i++)
    {
        // cout << Kp(i) * (ref(i) - cur(i)) << endl;
        u(i) = Kp(i) * (ref(i) - cur(i));
    }
};

// ////////////////////////////////////////////////
class stiffnessControl : public pdControl
{
public:
    double m = 1.2;
    double g = -9.81;

public:
    stiffnessControl(int n_, double dt_, Eigen::VectorXd Kp_, Eigen::VectorXd Kd_);
    virtual ~stiffnessControl();
    virtual void calculateControl(Eigen::VectorXd &ref, Eigen::VectorXd &cur) override;
    void calculateControlGravity(Eigen::VectorXd &ref, Eigen::VectorXd &cur);
};

stiffnessControl::stiffnessControl(int n_, double dt_, Eigen::VectorXd Kp_, Eigen::VectorXd Kd_)
    : pdControl(n_, dt_, Kp_, Kd_)
{
    cout << "\033[1;32mstiffness controller is defined\033[0m\n";
};

stiffnessControl::~stiffnessControl()
{
    cout << "\033[1;32mstiffness controller is deleted\033[0m\n";
};

void stiffnessControl::calculateControl(Eigen::VectorXd &ref, Eigen::VectorXd &cur)
{
    cout << "calc stiffness control..." << endl;
    pdControl::calculateControl(ref, cur); // you should specify which one you use!
    stiffnessControl::calculateControlGravity(ref, cur);

    cout << "u inside stiffness controller " << u << endl;
};

void stiffnessControl::calculateControlGravity(Eigen::VectorXd &ref, Eigen::VectorXd &cur)
{
    cout << "gravity is considered..." << endl;

    for (int i = 0; i < num_joint; i++)
    {
        u[i] += -m * g * sin(u[i]);
    }
};