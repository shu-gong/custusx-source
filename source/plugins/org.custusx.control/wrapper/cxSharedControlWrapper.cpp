#include <iostream>
#include <algorithm>
#include "Eigen/Core"
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>
#include "cxSharedControlWrapper.h"
#include "../control/sharedcontrol.cpp"

SharedControl::MatrixXd wrapPinv(MatrixXd A){
    return pinv(A);
}

SharedControl::MatrixXd wrapTeleJointSpace(double &kq, MatrixXd &dq_h, MatrixXd &q);
SharedControl::MatrixXd wrapTeleCartesianSpace(MatrixXd &kx, MatrixXd &dx_h, MatrixXd &x, MatrixXd &J);
SharedControl::double wrapFindDXR (MatrixXd &dx_set, double &last_num, :MatrixXd &x);
SharedControl::MatrixXd wrapAutoControl(MatrixXd &kx, MatrixXd &dx_set, double &last_num, MatrixXd &x, MatrixXd &J);
SharedControl::double  wrapComputeDSat(double &d_res, double &d_max, double &mu1, double &mu2, double &theta2, double &xi);
SharedControl::MatrixXd wrapSharedControl(MatrixXd &kx, MatrixXd &dx_h, MatrixXd &dx_r, MatrixXd &tube_set, MatrixXd &x, MatrixXd &J, double &mu1, double &mu2, double &theta2, double &xi);
