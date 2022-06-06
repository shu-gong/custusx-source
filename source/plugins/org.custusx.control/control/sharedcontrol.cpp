#include <iostream>
#include <algorithm>
#include "Eigen/Core"
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <Eigen/LU>
//#include "xxx.hpp"

#define DOF 3 
#define PI 3.1415926535898
using Eigen::Matrix4d;
using Eigen::MatrixXd;
using namespace std;
using std::vector;
typedef unsigned long DWORD;
//speed limit
const double MAXSPEED = 0.03;
const double MINSPEED = 0.001;


//compute Pseudo-inverse (svd)
Eigen::MatrixXd pinv(Eigen::MatrixXd A) {
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullU |
		Eigen::ComputeFullV); // M=USV*
	double pinvtoler = 1.e-8; // tolerance
	int row = A.rows();
	int col = A.cols();
	int k = min(row, col);
	Eigen::MatrixXd X = Eigen::MatrixXd::Zero(col, row);
	Eigen::MatrixXd singularValues_inv = svd.singularValues(); 
	Eigen::MatrixXd singularValues_inv_mat = Eigen::MatrixXd::Zero(col, row);
	for (long i = 0; i < k; ++i) {
		if (singularValues_inv(i) > pinvtoler)
			singularValues_inv(i) = 1.0 / singularValues_inv(i);
		else
			singularValues_inv(i) = 0;
	}
	for (long i = 0; i < k; ++i) {
		singularValues_inv_mat(i, i) = singularValues_inv(i);
	}
	X = (svd.matrixV()) * (singularValues_inv_mat) *
		(svd.matrixU().transpose()); // X=VS+U*

	return X;
}



	/**
MODE_1：Teleoperation_Joint_space (GUI: A B L +-）
	*Input：gain(kq), human desired position dq_h(A B L), current position q(A B L)
	*Output: Joint velocity (q_d)
	*/
Eigen::MatrixXd Teleoperation_Joint_space(double & kq, Eigen::MatrixXd & dq_h, Eigen::MatrixXd & q)
{
	Eigen::MatrixXd q_d(3, 1);
	Eigen::MatrixXd delta_q(3, 1);
	delta_q = q- dq_h;
	q_d = - kq * delta_q;
	return q_d;
}


	/**
MODE_1：Teleoperation_Cartesian_space (GUI: X Y Z +-）
	*Input：gain kx(3,3), human desired position dx_h(X Y Z), current position x(X Y Z), Jacobian J(3,3)
	*Output: Joint velocity (q_d)
	*/
Eigen::MatrixXd Teleoperation_Cartesian_space(Eigen::MatrixXd & kx, Eigen::MatrixXd & dx_h, Eigen::MatrixXd & x, Eigen::MatrixXd & J)
{
	Eigen::MatrixXd q_d(3, 1);
	Eigen::MatrixXd delta_x(3, 1);
	delta_x =  x - dx_h;
	q_d = -kx * J.inverse()*delta_x;
	return q_d;
}

/*find the desired robot position from the desired path set
*Input：dx_set: robot desired position set n*3（obtained by "find route to target"）;
	    last_num: The number corresponding to the last desired robot position ; 
		x: current position(X Y Z);
 Output: num: the number of desired robot position in set
*/
double find_dxr (Eigen::MatrixXd & dx_set, double & last_num, Eigen::MatrixXd & x)
{
	//find the nearest point in the dx_set (from the last search results)
	double num = last_num;
	Eigen::MatrixXd dx_last(3, 1), dx_r(3, 1);
	dx_last << dx_set(last_num, 0) , dx_set(last_num, 1) , dx_set(last_num, 2);
	dx_r = dx_last;
	double len_min = (x - dx_last).norm();
	for (int i = last_num; i < dx_set.rows(); ++i)
	{
		Eigen::MatrixXd dx(3, 1);
		dx << dx_set(i, 0) , dx_set(i, 1) , dx_set(i, 2);
		double dis = (x - dx).norm();
		if (dis < len_min)
		{
			len_min = dis;
			num = i;
			dx_r = dx;
		}
	}
	return num;
}

/**
MODE_2：Automatic control（Prohibit human input）
	*Input：gain kx(3,3); dx_set: robot desired position set n*3（obtained by "find route to target"）;
	        last_num: The number corresponding to the last desired robot position ; 
			current position x(X Y Z), Jacobian J(3,3)
	*Output: Joint velocity (q_d) 3*1
	*/
Eigen::MatrixXd Automatic_control(Eigen::MatrixXd & kx, Eigen::MatrixXd & dx_set, double & last_num, Eigen::MatrixXd & x, Eigen::MatrixXd & J)
{
	Eigen::MatrixXd q_d(3, 1);
	Eigen::MatrixXd delta_x(3, 1);
	Eigen::MatrixXd dx_r(3, 1);
	//find the nearest point in the dx_set (from the last search results)
	double num = find_dxr(dx_set, last_num, x);
	dx_r << dx_set(num, 0) , dx_set(num, 1) , dx_set(num, 2);
	delta_x =  x - dx_r ;
	q_d = - kx * J.inverse()*delta_x;
	return q_d;
}
/**
*Compute_d_sat
*Input：d_res, d_max, 
        mu1, mu2, theta2, xi: parameters;
*Output: d_sat
*/
double  compute_d_sat(double & d_res, double & d_max, double & mu1, double & mu2, double & theta2, double & xi)
{
	double d_sat;
	double mud = mu1 * d_res;
	double h = 1 + xi * exp(-theta2 * (d_max - mu2 * d_res));
	double xi_inv = 1 / xi;
	double xxx = pow(h, xi_inv);
	d_sat = mud / xxx;
	return d_sat;
}
/**
*MODE_3：Shared control（allowed human）
*Input：gain ; human desired position (dx_h)；robot desired position (dx_r); 
        tube_set n*3; current position x(X Y Z); Jacobian J(3,3); 
		mu1, mu2, theta2, xi：parameters ;
		Q_1r,Q_2r,Q_h:parameters;
*Output: Joint velocity (q_d)
*/
Eigen::MatrixXd Shared_control(Eigen::MatrixXd & kx, Eigen::MatrixXd & dx_h, Eigen::MatrixXd & dx_r, Eigen::MatrixXd & tube_set, Eigen::MatrixXd & x, Eigen::MatrixXd & J, double & mu1, double & mu2, double & theta2, double & xi)
{
	Eigen::MatrixXd q_d(3, 1);
	//是否需要一个dx_r的调整（后期可添加）
	/*safety index*/
	/*find the minimum distance to the robot desired path from the tube_set */
	Eigen::MatrixXd tube_near(3, 1);
	tube_near << tube_set(0, 0) , tube_set(0, 1) , tube_set(0, 2);
	double d_res = (dx_r - tube_near).norm();
	for (int i = 0; i < tube_set.rows(); ++i)	{
		Eigen::MatrixXd tube_cur(3, 1);
		tube_cur << tube_set(i, 0) , tube_set(i, 1) , tube_set(i, 2);
		double dis = (x - tube_cur).norm();
		if (dis < d_res)
		{
			d_res = dis;
			tube_near = tube_cur;
		}
	}
	double d = (x - dx_r).norm();
	double d_max = min(d, d_res);
	double d_sat = compute_d_sat(d_res, d_max, mu1, mu2, theta2, xi);
	double lamta;
	lamta = sqrt(d_res*d_res - d_sat * d_sat);
	lamta = lamta / d_res;
	
	Eigen::MatrixXd delta_xh = x - dx_h;
	Eigen::MatrixXd delta_xr = x - dx_r;

	/*MPC CONTROLLER: compute cost (unfinished)*/
	/*Eigen::MatrixXd C_r = 0.5 * delta_xr.transpose() * Q_1r * delta_xr+0.5*q_d.transpose() * Q_2r * q_d;
	Eigen::MatrixXd C_h = 0.5 * delta_xh.transpose() * Q_h * delta_xh;
	Eigen::MatrixXd C = lamta * C_h + (1 - lamta)*C_r;*/

	//simple version
	q_d = kx * J.inverse()*(lamta* delta_xh+ (1 - lamta)*delta_xr);
	return q_d;
}

int main()
{
	Eigen::MatrixXd J(3,3);
	Eigen::MatrixXd tube;
	//test 3d data (tube-like)
	//ifstream myfile("E:/code_c++/shared_control/sharedcontrol/sharedcontrol/data_3d.txt");
	//int i = 0;
	//while (!myfile.eof()) //直到文件结尾
	//{
	//	myfile >> tube(i,0) >> tube(i, 1)>> tube(i, 2);
	//	i++;
	//}
	//myfile.close();
	//
}

