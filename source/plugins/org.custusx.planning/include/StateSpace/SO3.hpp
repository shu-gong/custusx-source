//
// Created by xcy on 2020/12/15.
//

#ifndef NURSINGROBOT_SO3_H
#define NURSINGROBOT_SO3_H

#include "StateSpace.hpp"
#include <iostream>
#include <utility>
#include "../macros/class_forward.h"

namespace state_space {

    /**
     * @brief transfers a R3 vector to a so3 matirx
     * @param omega a R3 vector representing w
     * @return a so3 matrix
     */
    static so_3 VecToso3(const Eigen::Vector3d &omega)
    {
        so_3 w_x;
        w_x << 0, -omega[2], omega[1],
                omega[2], 0, -omega[0],
                -omega[1], omega[0], 0;
        return w_x;
    }

    /**
     * @brief transfers a so3 matrix to a R3 vector
     * @param a_so3 a so3 matrix
     * @return a R3 vector
     */
    static R3 so3ToVec(const so_3 &a_so3)
    {
        return R3{-a_so3(1, 2), a_so3(0, 2), -a_so3(0, 1)};
    }

    DONT_ALIGN_CLASS_STL_FORWARD(SO3)

    class SO3 : private virtual StateSpace<SO3> {
    private:
        R3 _twist_2d_;

        SO_3 SO3_MATRIX_;

        const unsigned int _dimensions = 3;

        /**
         *
         * @return so3 matrix of this SO3 object
         */
        so_3 _calculate_so3() const
        { return so_3{VecToso3(Vector())}; };

        so_3 _calculate_unit_so3() const
        { return so_3{VecToso3(Axis())}; };
    public:

        explicit SO3(unsigned int dimensions = 3)
        {
            _twist_2d_.setZero();
            SO3_MATRIX_.setIdentity();
        }

        SO3(const SO3 &SO3_)
                : StateSpace(SO3_),
                  _twist_2d_(SO3_._twist_2d_),
                  SO3_MATRIX_(SO3_.SO3_MATRIX_)
        {

        }

        explicit SO3(R3 twist)
                : _twist_2d_(std::move(twist))
        {
            so_3 so_3_ = NearZero(Theta()) ? Eigen::Matrix3d::Identity() : VecToso3(Vector());
            SO3_MATRIX_ = MatrixExp(so_3_);
        }

        /**
         * \note Construct SO3 using rotation_matrix, change that rotation matrix if it's not orthogonal
         * */
        explicit SO3(const SO_3 &rotation_matrix)
        {

            //R3 twist = so3ToVec(MatrixLog(rotation_matrix));
            Eigen::AngleAxisd rotation_vector(rotation_matrix);
            _twist_2d_ = rotation_vector.axis() * rotation_vector.angle();
            SO3_MATRIX_ = rotation_vector.matrix();
        }

        explicit SO3(const Eigen::Vector4d &quaternion_)
        {
            Eigen::Quaterniond quaternion(quaternion_);
            *this = SO3(quaternion.toRotationMatrix());
        }

        explicit SO3(double roll, double pitch, double yaw)
        {
            Eigen::AngleAxisd rollAngle(Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()));
            Eigen::AngleAxisd pitchAngle(Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY()));
            Eigen::AngleAxisd yawAngle(Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()));
            Eigen::Matrix3d rotation_matrix{yawAngle * pitchAngle * rollAngle};
            *this = SO3(rotation_matrix);
        }

        explicit SO3(const double *data_ptr, unsigned int dimensions = 3)
        {
            Eigen::Vector3d temp_twist(data_ptr);
            *this = SO3(temp_twist);
        }

        ~SO3() override = default;

        R3 Vector() const
        { return _twist_2d_; };

        R3 Axis() const
        { return _twist_2d_.normalized(); };

        double Theta() const
        { return _twist_2d_.norm(); };

        SO_3 SO3Matrix() const
        { return SO3_MATRIX_; };

        so_3 Unitso3Matrix() const
        { return _calculate_unit_so3(); };

        so_3 so3Matrix() const
        { return _calculate_so3(); };

        Eigen::Vector4d Quaternion() const
        {
            Eigen::Quaterniond rotation{SO3_MATRIX_};
            return rotation.coeffs();
        };

        Eigen::Vector3d RPY() const
        {
            return SO3_MATRIX_.eulerAngles(0, 1, 2);
        };

        double norm() const override
        {
            return _twist_2d_.norm();
        }

        SO3 operator+(const SO3 &input) const override
        {
            SO_3 result;
            result.setZero();
            result.noalias() += this->SO3Matrix() * input.SO3Matrix();
            return SO3(result);
        };

        SO3 operator-(const SO3 &input) const override
        {
            SO_3 tmp_matrix;
            tmp_matrix.setZero();
            tmp_matrix.noalias() += input.SO3Matrix().inverse() * this->SO3Matrix();
            return SO3(tmp_matrix);
        };

        SO3 operator*(double s) const override
        {
            R3 temp_twist{s * this->Vector()};
            return SO3(temp_twist);
        };

        friend SO3 operator*(double s, const SO3 &input)
        {
            return input * s;
        }

        SO3 operator()(double theta) const override
        {
            R3 temp_twist(this->Axis() * theta);
            return SO3(temp_twist);
        };

        bool operator==(const SO3 &other) const override
        {
            return _twist_2d_ == other._twist_2d_;
        }

        SO3 &operator=(const SO3 &input)
        {
            StateSpace<SO3>::operator=(input);
            this->_twist_2d_ = input._twist_2d_;
            this->SO3_MATRIX_ = input.SO3_MATRIX_;
        }

        SO3 inverse() const override
        {
            R3 twist(-Axis() * Theta());
            return SO3(twist);
        };

        static SO3 Zero(unsigned int dimensions = 3)
        {
            return SO3(dimensions);
        }
        static SO3 UnitX()
        {
            return SO3(R3{1,0,0});
        }
        static SO3 UnitY()
        {
            return SO3(R3{0,1,0});
        }
        static SO3 UnitZ()
        {
            return SO3(R3{0,0,1});
        }
        unsigned int Dimensions() const override
        {
            return _dimensions;
        };

        const double *data() const override
        {
            return this->_twist_2d_.data();
        };

        SO3 random(std::default_random_engine &randomEngine, const Eigen::MatrixX2d *bounds_ptr) const override
        {
            //Effective Sampling and Distance Metrics for 3D Rigid Body Path Planning [c]
            //James J. Kuffner
            //use the uniformly sampling unit Quaternion
            std::uniform_real_distribution<double> x_distribution(0, 1);
            /*here we use convention of XYZ YPR.
            double roll,pitch,yaw;
            yaw = 2*M_PI*x_distribution(randomEngine)-M_PI;
            pitch = std::acos(1-2*x_distribution(randomEngine))-M_PI_2;
            roll = 2*M_PI*x_distribution(randomEngine)-M_PI;*/
            //uniformly sampling using unit quaternions;
            double s = x_distribution(randomEngine);
            double sigma1 = std::sqrt(1 - s);
            double sigma2 = std::sqrt(s);
            double theta1, theta2;
            theta1 = 2 * M_PI * x_distribution(randomEngine);
            theta2 = 2 * M_PI * x_distribution(randomEngine);
            Eigen::Vector4d random_quaternion{sin(theta1) * sigma1, cos(theta1) * sigma1, sin(theta2) * sigma2,
                                              cos(theta2) * sigma2};
            return SO3(random_quaternion);

        };

        double distance(const SO3 &to) const override
        {
            //Smooth invariant interpolation of rotations
            //F.park & B.Ravani
            //pr = ||log(Q1^{-1}*Q2)||, which is bi-invariant
            return (to - *this).Vector().norm();
        };
        /**
         * \brief according to Jonathan H. Manton
         * A GLOBALLY CONVERGENT NUMERICAL ALGORITHM FOR COMPUTING THE CENTRE OF MASS ON COMPACT LIE GROUPS
         * @param list n elements of SO3
         * @return center of mass
         */
        static SO3 average(const vector_SO3 & list,double error_thresh = 1e-3)
        {
            auto average_element = list.front();
            while(true)
            {
                Eigen::Vector3d  omega{Eigen::Vector3d::Zero()};
                for(const auto & item:list){
                    omega += (item-average_element).Vector();
                }
                omega *= (double)1.0/list.size();
                if(omega.norm() < error_thresh)
                    return average_element;
                else
                    average_element = average_element+SO3(omega);
            }
        }

        static SO_3 MatrixExp(const so_3 &so3_)
        {
            R3 twist{so3ToVec(so3_)};
            double theta = twist.norm();
            if (NearZero(theta)) {
                return Eigen::Matrix3d::Identity();
            } else {
                SO_3 unit_so3 = VecToso3(twist.normalized());
                return Eigen::Matrix3d::Identity() + std::sin(theta) * unit_so3 +
                       (1 - std::cos(theta)) * unit_so3 * unit_so3;
            }
        }

        static so_3 MatrixLog(const SO_3 &SO3_)
        {
            double acos_input = (SO3_.trace() - 1) / 2.0;
            Eigen::Matrix3d m_ret(Eigen::Matrix3d::Zero());
            if (acos_input >= 1)
                return m_ret;
            else if (acos_input <= -1) {
                Eigen::Vector3d omega;
                if (!NearZero(1 + SO3_(2, 2)))
                    omega = (1.0 / std::sqrt(2 * (1 + SO3_(2, 2)))) *
                            Eigen::Vector3d(SO3_(0, 2), SO3_(1, 2), 1 + SO3_(2, 2));
                else if (!NearZero(1 + SO3_(1, 1)))
                    omega = (1.0 / std::sqrt(2 * (1 + SO3_(1, 1)))) *
                            Eigen::Vector3d(SO3_(0, 1), 1 + SO3_(1, 1), SO3_(2, 1));
                else
                    omega = (1.0 / std::sqrt(2 * (1 + SO3_(0, 0)))) *
                            Eigen::Vector3d(1 + SO3_(0, 0), SO3_(1, 0), SO3_(2, 0));

                m_ret = VecToso3(omega * M_PI);
            } else {
                Eigen::AngleAxisd rotation_vector(SO3_);
                double theta = rotation_vector.angle();
                //Warning:
                // here exists a multiple value problem,temporarily fixed by using angle axis;
                //double theta = std::acos(acosinput);
                m_ret = theta * (SO3_ - SO3_.transpose()) / (2.0 * sin(theta));
            }
            return m_ret;
        }

        /**
        * \brief Check whether the given matrix is really (mathematically) an orthogonal (rotation) matrix.
        */
        static inline bool isOrthogonal(const state_space::SO_3 &matrix)
        {
            return (matrix * matrix.transpose()).isApprox(state_space::SO_3::Identity(),
                                                          Eigen::NumTraits<double>::dummy_precision());
        }

        /**
         * \brief Project a 3x3 matrix into SO3
         * @param matrix a 3X3 matrix
         * @return a mathematically orthogonal (least square solution) matrix
         */
        static state_space::SO_3 projectToSO3(const state_space::SO_3 &matrix)
        {
            Eigen::JacobiSVD<state_space::SO_3> svd(matrix, Eigen::ComputeFullU | Eigen::ComputeFullV);
            SO_3 R = svd.matrixU() * svd.matrixV().transpose();
            if (R.determinant() < 0)
                // In this case the result may be far from M; reverse sign of 3rd column
                R.col(2) *= -1;
            return R;
        }

        friend std::ostream &operator<<(std::ostream &s, const SO3 &input)
        {
            s << input._twist_2d_.transpose();
            return s;
        }
    };

}


#endif //NURSINGROBOT_SO3_H
