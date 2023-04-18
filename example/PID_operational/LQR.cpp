/*
Goal
- Given nonlinear dynamics, we want to run LQR over the linearized trajectory
- Expected performance: if the error is not so large or if the system is not too nonlinear, LQR controller might work well

Tasks
1. linearize the dynamics over the nominal trajectory
2. Set up A, B, with Q R cost with discrete time dynamics
3. Use eigen library to compute matrix
4. Show results in figure
5. postprocessing (e.g., use reference to decrease memory usage, etc)
*/

// -----------------------------------------
#include <iostream>
#include <Eigen/Dense>

using namespace std;

// -----------------------------------------


class LQR{
    private:
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A;
        Eigen::MatrixXd B;
        Eigen::MatrixXd Q;
        Eigen::MatrixXd R;

        Eigen::MatrixXd K;

    public:
        LQR(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &A_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &B_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &Q_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &R_);
        ~LQR();
        void runLQR();

};


LQR::LQR(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &A_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &B_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &Q_, const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &R_) : 
A(A_), B(B_), Q(Q_), R(R_){
    cout << "LQR object is created" << endl;

};
LQR::~LQR(){

};

void LQR::runLQR(){
    // Eigen::lqr();

};


// -----------------------------------------
int main(){
    cout << "LQR main" << endl;

    Eigen::Matrix2d A = Eigen::Matrix2d::Zero();
    A(0, 1) = 1;
    Eigen::Matrix<double, 2, 1> B;
    B << 0, 1;

    Eigen::Matrix2d Q = Eigen::Matrix2d::Identity();
    Eigen::Matrix<double, 1, 1> R;
    R << 0.1;


    LQR lqr(A, B, Q, R);

    lqr.runLQR();

    return 0;
}