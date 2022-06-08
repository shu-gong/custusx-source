#ifndef NURSINGROBOT_STATESPACE_HPP
#define NURSINGROBOT_STATESPACE_HPP

#include <vector>
#include <array>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/StdVector>
#include <random>

namespace state_space {
    //exponential coordinate of se(3) s = [w,v]
    typedef Eigen::Matrix<double, 6, 1> R6;

    //lie algebra se(3) of the lie group SE(3)
    typedef Eigen::Matrix4d se_3;

    //lie group SE(3)
    typedef Eigen::Matrix4d SE_3;

    //exponential coordinate of so(3)
    typedef Eigen::Vector3d R3;

    //lie algebra so(3) of the lie group SO(3)
    typedef Eigen::Matrix3d so_3;

    //lie group SO(3)
    typedef Eigen::Matrix3d SO_3;

    //adjoint matrix 6X6 for Lie bracket
    typedef Eigen::Matrix<double, 6, 6> adjoint_mat;

    typedef Eigen::Matrix<double, 6, 6> jacobian_mat;

    /**\note: 2e-8 denotes 1e-6 degree precision*/
    static bool NearZero(const double val)
    {
        return (std::abs(val) < 1e-8);
    }

    /**
    * A state space represents the set of possible states for a planning problem.
    * for example Rn SO2 SO3 SE3 SE3
    * This class is abstract and must be subclassed in order to provide actual
    * functionality.
    */
    template<typename T>
    class StateSpace {
    public:
        StateSpace() = default;

        virtual ~StateSpace() = default;

        //
        virtual T operator+(const T &input) const = 0;

        virtual T operator-(const T &input) const = 0;

        virtual T operator*(double s) const = 0;

        virtual T operator()(double theta) const = 0;

        virtual bool operator==(const T &other) const = 0;

        virtual T inverse() const = 0;

        virtual T random(std::default_random_engine &randomEngine, const Eigen::MatrixX2d *bounds_ptr) const = 0;

        virtual double distance(const T &to) const = 0;

        virtual double norm() const = 0;

        virtual const double *data() const = 0;

        virtual unsigned int Dimensions() const = 0;
    };


}


#endif //NURSINGROBOT_STATESPACE_HPP
