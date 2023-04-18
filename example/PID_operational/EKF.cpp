#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main()
{
    // Define state variables
    double x, y, vx, vy;

    int dt = 0.01;
    int num_steps = 100;

    double R_meas = 0.01;

    // Define measurement variables
    double x_meas, y_meas;

    // Define state transition model
    Matrix4d F;
    F << 1, 0, dt, 0,
         0, 1, 0, dt,
         0, 0, 1, 0,
         0, 0, 0, 1;

    Matrix4d Q;
    Q = Eigen::Matrix4d::Constant(0.001);

    // Define measurement model
    Matrix<double, 2, 4> H;
    H << 1, 0, 0, 0,
         0, 1, 0, 0;

    // Initialize state and covariance matrices
    Vector4d x_hat = Vector4d::Zero();
    Matrix4d P = Matrix4d::Identity();

    // Loop over time steps
    for (int i = 0; i < num_steps; i++)
    {
        // Prediction step
        x_hat = F * x_hat;
        P = F * P * F.transpose() + Q;

        // Update step
        Vector2d z = Vector2d(x_meas, y_meas);
        Vector2d y = z - H * x_hat;
        Matrix2d S = H * P * H.transpose();


    Matrix2d R = Matrix2d::Identity() * R_meas;
    Matrix<double, 4, 2> K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
    x_hat += K * y;
    P = (Matrix4d::Identity() - K * H) * P;

    cout << "xhat: " << x_hat << endl;
}

return 0;


}