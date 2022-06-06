#include <iostream>
#include <algorithm>
#include "Eigen/Core"
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>
#include "vtkForwardDeclarations.h"
#include "cxForwardDeclarations.h"
#include "vtkPolyData.h"
#include "cxPointMetric.h"

#ifndef CXSHAREDCONTROLWRAPPER_H_
#define CXSHAREDCONTROLWRAPPER_H_

namespace cx{

#define DOF 3 
#define PI 3.1415926535898

using Eigen::Matrix4d;
using Eigen::MatrixXd;
using std::vector;

using namespace std;

typedef unsigned long DWORD;
typedef Eigen::MatrixXd MatrixXd;

//speed limit
const double MAXSPEED = 0.03;
const double MINSPEED = 0.001;


class SharedControlWrapper{

private:
    MatrixXd pointMetric2MatrixXd(PointMetricPtr* pointMetricPtr);

public:

    //compute Pseudo-inverse (svd)
    MatrixXd wrapPinv(MatrixXd A) ;

    	/**
    MODE_1：Teleoperation_Joint_space (GUI: A B L +-）
	*Input：gain(kq), human desired position dq_h(A B L), current position q(A B L)
	*Output: Joint velocity (q_d)
	*/
    MatrixXd wrapTeleJointSpace(double &kq, MatrixXd &dq_h, MatrixXd &q);
    MatrixXd wrapTeleJointSpace(double &kq, PointMetricPtr* wrap_dq_h, PointMetricPtr* wrap_q);

	/**
    MODE_1：Teleoperation_Cartesian_space (GUI: X Y Z +-）
	*Input：gain kx(3,3), human desired position dx_h(X Y Z), current position x(X Y Z), Jacobian J(3,3)
	*Output: Joint velocity (q_d)
	*/
    MatrixXd wrapTeleCartesianSpace(Ma

    /*find the desired robot position from the desired path set
    *Input：dx_set: robot desired position set n*3（obtained by "find route to target"）;
	    last_num: The number corresponding to the last desired robot position ; 
		x: current position(X Y Z);
    Output: num: the number of desired robot position in set
    */
    double wrapFindDXR(MatrixXd & dx_set, double & last_num, MatrixXd & x);
    double wrapFIndDXR(PointMetricPtr* wrap_dx_set, double &last_num, PointMetricPtr* wrap_x);
    trixXd &kx, MatrixXd &dx_h, MatrixXd &x, MatrixXd &J);
        MatrixXd wrapTeleCartesianSpace(PointMetricPtr* wrap_kx, PointMetricPtr* wrap_dx_h, PointMetricPtr* wrap_x, PointMetricPtr* wrap_J);


    /**
    MODE_2：Automatic control（Prohibit human input）
	*Input：gain kx(3,3); dx_set: robot desired position set n*3（obtained by "find route to target"）;
	        last_num: The number corresponding to the last desired robot position ; 
			current position x(X Y Z), Jacobian J(3,3)
	*Output: Joint velocity (q_d) 3*1
	*/
    MatrixXd wrapAutoControl(MatrixXd &kx, MatrixXd &dx_set, double &last_num, MatrixXd &x, MatrixXd &J);
    MatrixXd wrapAutoControl(PointMetricPtr* wrap_kx, PointMetricPtr* wrap_dx_set, double &last_num, PointMetricPtr* wrap_x, PointMetricPtr* wrap_J);


    /**
    *Compute_d_sat
    *Input：d_res, d_max, 
        mu1, mu2, theta2, xi: parameters;
    *Output: d_sat
    */
    double  wrapComputeDSat(double &d_res, double &d_max, double &mu1, double &mu2, double &theta2, double &xi);
    
    /**
    *MODE_3：Shared control（allowed human）
    *Input：gain ; human desired position (dx_h)；robot desired position (dx_r); 
        tube_set n*3; current position x(X Y Z); Jacobian J(3,3); 
		mu1, mu2, theta2, xi：parameters ;
		Q_1r,Q_2r,Q_h:parameters;
    *Output: Joint velocity (q_d)
    */
    MatrixXd wrapSharedControl(MatrixXd &kx, MatrixXd &dx_h, MatrixXd &dx_r, MatrixXd &tube_set, MatrixXd &x, MatrixXd &J, double &mu1, double &mu2, double &theta2, double &xi);

};
}
#endif /* CXSHAREDCONTROL_H_ */
