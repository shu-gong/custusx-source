#ifndef NURSINGROBOT_SE3_HPP
#define NURSINGROBOT_SE3_HPP

#include "StateSpace.hpp"
#include "SO3.hpp"
#include "rn.hpp"

namespace state_space {

    /**
     * @brief transfers a se3 matrix to a twist vector
     * @param a_se3
     * @return a twist
     */
    static R6 se3ToVec(const se_3 &a_se3)
    {
        R6 twist;
        twist << so3ToVec(a_se3.block<3, 3>(0, 0)), a_se3.block<3, 1>(0, 3);
        return twist;
    }

    /**
     * @brief transfers a twist to se3 matirx
     * @param a_twist
     * @return a se3 matrix
     */
    static se_3 VecTose3(const R6 &a_twist)
    {
        se_3 se_3_;
        se_3_ << VecToso3(a_twist.block<3, 1>(0, 0)), a_twist.block<3, 1>(3, 0),
                0, 0, 0, 0;
        return se_3_;
    }

    /**
     * @brief gets adjoint matrix of SE3 object
     * @param a_SE3
     * @return a 6x6 matrix, which is the adjoint matrix of @a_SE3
     */
    static adjoint_mat GetAdjoint(const SE_3 &a_SE3)
    {
        adjoint_mat ad_ret;
        ad_ret << a_SE3.block<3, 3>(0, 0), Eigen::Matrix3d::Zero(),
                VecToso3(a_SE3.block<3, 1>(0, 3)) * a_SE3.block<3, 3>(0, 0), a_SE3.block<3, 3>(0, 0);
        return ad_ret;
    }

    DONT_ALIGN_CLASS_STL_FORWARD(SE3)

    class SE3 : public virtual StateSpace<SE3> {
    protected:
        R6 _twist_3d_;

        SE_3 SE3_matrix_;

        const unsigned int _dimensions = 6;

        /**
         *
         * @return se3 matrix of this SE3 object
         */
        se_3 _calculate_se3() const
        {
            return se_3{VecTose3(Vector())};
        };

        /**
         *
         * @return unit se3 matrix of this SE3 object
         */
        se_3 _calculate_unitse3() const
        {
            return se_3{VecTose3(Axis())};
        };
    public:

        explicit SE3(unsigned int dimensions = 6)
        {
            _twist_3d_.setZero();
            SE3_matrix_.setIdentity();
        };

        SE3(const SE3 &a_SE3)
                : StateSpace(a_SE3),
                  _twist_3d_(a_SE3._twist_3d_),
                  SE3_matrix_(a_SE3.SE3_matrix_)
        {

        }

        explicit SE3(const double *data_ptr, unsigned int dimensions = 6)
        {
            *this = SE3(state_space::R6(data_ptr));
        }

        explicit SE3(const R6 &twist)
        {
            _twist_3d_ = twist;
            se_3 se_3_;
            if (!NearZero(Theta()))
                se_3_ = VecTose3(_twist_3d_);
            else
                se_3_ << Eigen::Matrix3d::Identity(), _twist_3d_.block<3, 1>(3, 0),
                        0, 0, 0, 0;
            SE3_matrix_ = MatrixExp(se_3_);
        }

        explicit SE3(const Eigen::Matrix<double, 7, 1> &pose_with_quaternion)
        {
            Eigen::Vector3d translation{pose_with_quaternion.block<3, 1>(0, 0)};
            Eigen::Quaterniond rotation{pose_with_quaternion.block<4, 1>(3, 0)};
            SE3_matrix_  << rotation.toRotationMatrix(), translation,
                            0, 0, 0, 1;
            _twist_3d_ = se3ToVec(MatrixLog(SE3_matrix_));
        }

        explicit SE3(const Eigen::Affine3d &transformation_matrix)
        {
            *this = SE3(transformation_matrix.matrix());
        }

        /**
         * \note Construct SE3 using transform matrix may lose some data, if it's rotation part isn't orthogonal
         */
        explicit SE3(const SE_3 &transformation_matrix)
        {
            SO_3 temp_SO_3(transformation_matrix.block<3, 3>(0, 0));
            *this = SE3(SO3(temp_SO_3), transformation_matrix.block<3, 1>(0, 3));
        }

        SE3(const SO3 &SO3_part, const Eigen::Vector3d &translation_part)
        {
            SE3_matrix_ << SO3_part.SO3Matrix(), translation_part,
                    0, 0, 0, 1;
            _twist_3d_ = se3ToVec(MatrixLog(SE3_matrix_));
        }

        explicit SE3(const std::vector<double> &vector_input)
        {
            if (vector_input.size() == 6) {
                *this = SE3(R6(vector_input.data()));
                return;
            } else if (vector_input.size() == 7) {
                *this = SE3(Eigen::Matrix<double, 7, 1>(vector_input.data()));
                return;
            } else {
                throw std::invalid_argument(
                        "only support initialize with 6 or 7 coefficients within a vector\n");
            }
        }

        ~SE3() override = default;

        R6 Vector() const
        { return _twist_3d_; };

        R6 Axis() const
        { return getNormalizedTwist(_twist_3d_); };

        double Theta() const
        {
            /*
             * Only takes pure rotation or translation into account, this is not general.
             * But for robotics, it's sufficient.
             */
            if (!NearZero(_twist_3d_.norm()) && NearZero(_twist_3d_.block<3, 1>(0, 0).norm()))
                return _twist_3d_.block<3, 1>(3, 0).norm();
            else
                return _twist_3d_.block<3, 1>(0, 0).norm();
        };

        SE_3 SE3Matrix() const
        { return SE3_matrix_; };

        se_3 se3Matrix() const
        { return _calculate_se3(); };

        se_3 Unitse3Matrix() const
        { return _calculate_unitse3(); };

        SO3 SO3Part() const
        {
            R3 omega{_twist_3d_.block<3, 1>(0, 0)};
            return SO3(omega);
        };

        Eigen::Vector3d translationPart() const
        {
            return SE3_matrix_.block<3, 1>(0, 3);
        }
        Eigen::Vector4d HomoTransPart() const
        {
            return SE3_matrix_.col(3);
        }
        Eigen::Matrix<double, 7, 1> pose_with_quaternion() const
        {
            Eigen::Matrix<double, 7, 1> result;
            result << SE3_matrix_.block<3, 1>(0, 3), SO3Part().Quaternion();
            return result;
        };

        const double *data() const override
        {
            return this->_twist_3d_.data();
        };

        adjoint_mat Adjoint()
        {
            const SE_3 &T = this->SE3_matrix_;
            adjoint_mat ad_ret;
            ad_ret << T.block<3, 3>(0, 0), Eigen::Matrix3d::Zero(),
                    VecToso3(T.block<3, 1>(0, 3)) * T.block<3, 3>(0, 0), T.block<3, 3>(0, 0);
            return ad_ret;
        }

        SE3 operator+(const SE3 &input) const override
        {
            SE_3 result;
            result.setZero();
            result.noalias() += this->SE3Matrix() * input.SE3Matrix();
            return SE3(result);
        };

        SE3 operator-(const SE3 &input) const override
        {
            SE_3 tmp_matrix;
            tmp_matrix.setZero();
            tmp_matrix.noalias() += input.SE3Matrix().inverse() * this->SE3Matrix();
            return SE3(tmp_matrix);
        };

        SE3 operator*(double s) const override
        {
            R6 temp_twist{s * this->Vector()};
            return SE3(temp_twist);
        };

        friend SE3 operator*(double s, const SE3 &input)
        {
            return input * s;
        };

        SE3 operator()(double theta) const override
        {
            R6 temp_twist;
            temp_twist.setZero();
            if(!NearZero(this->_twist_3d_.norm()))
                temp_twist = state_space::R6(this->Axis() * theta);

            return SE3(temp_twist);
        };

        SE3 &operator=(const SE3 &input)
        {
            StateSpace<SE3>::operator=(input);
            this->_twist_3d_ = input._twist_3d_;
            this->SE3_matrix_ = input.SE3_matrix_;
        }

        bool operator==(const SE3 &other) const override
        {
            return _twist_3d_ == other._twist_3d_;
        }

        static SE3 Zero(unsigned int dimensions = 6)
        {
            return SE3(dimensions);
        }

        double norm() const override
        {
            return _twist_3d_.norm();
        }

        unsigned int Dimensions() const override
        {
            return _dimensions;
        };

        SE3 inverse() const override
        {
            R6 twist(-Axis() * Theta());
            return SE3(twist);
        };
        /**
         * \brief according to Jonathan H. Manton
         * A GLOBALLY CONVERGENT NUMERICAL ALGORITHM FOR COMPUTING THE CENTRE OF MASS ON COMPACT LIE GROUPS
         * @param list n elements of SO3
         * @return center of mass
         */
        static SE3 average(const vector_SE3 & list,double error_thresh = 1e-3)
        {
            auto average_element = list.front();
            while(true)
            {
                R6 omega{R6::Zero()};
                for(const auto & item:list){
                    omega += (item-average_element).Vector();
                }
                omega *= (double)1.0/list.size();
                if(omega.norm() < error_thresh)
                    return average_element;
                else
                    average_element = average_element+SE3(omega);
            }
        }

        SE3 random(std::default_random_engine &randomEngine, const Eigen::MatrixX2d *bounds_ptr) const override
        {
            return SE3(SO3().random(randomEngine, nullptr),
                       Rn::Zero(3).random(randomEngine, bounds_ptr).Vector());
        };

        double distance(const SE3 &to) const override
        {
            //similar to SO3 distance
            return (to - *this).Vector().norm();
        };

        static SE_3 MatrixExp(const se_3 &se3_)
        {
            R3 twist{so3ToVec(se3_.block<3, 3>(0, 0))};
            SO3 SO3_part(twist);

            SE_3 m_ret;
            if (NearZero(SO3_part.Theta())) {
                m_ret << SO3_part.SO3Matrix(), se3_.block<3, 1>(0, 3),
                        0, 0, 0, 1;
            } else {
                Eigen::Matrix3d J = Eigen::Matrix3d::Identity() * SO3_part.Theta() + (1 - std::cos(SO3_part.Theta()))
                                                                                     * SO3_part.Unitso3Matrix() +
                                    (SO3_part.Theta()
                                     - std::sin(SO3_part.Theta())) * SO3_part.Unitso3Matrix() *
                                    SO3_part.Unitso3Matrix();

                m_ret << SO3_part.SO3Matrix(), J * se3_.block<3, 1>(0, 3) / SO3_part.Theta(),
                        0, 0, 0, 1;
            }

            return m_ret;
        }

        static se_3 MatrixLog(const SE_3 &SE3_)
        {
            SO_3 tmp_matrix{SE3_.block<3, 3>(0, 0)};
            SO3 SO3_part(tmp_matrix);

            double theta = SO3_part.Theta();
            se_3 m_ret;
            if (NearZero(theta)) {
                m_ret << Eigen::Matrix3d::Zero(), SE3_.block<3, 1>(0, 3),
                        0, 0, 0, 0;
            } else {
                Eigen::Matrix3d J_inverse = Eigen::Matrix3d::Identity() - SO3_part.so3Matrix() / 2.0 +
                                            (1.0 / theta - 1.0 / std::tan(theta / 2.0) / 2) * SO3_part.so3Matrix() *
                                            SO3_part.so3Matrix() / theta;

                m_ret << SO3_part.so3Matrix(), J_inverse * SE3_.block<3, 1>(0, 3),
                        0, 0, 0, 0;
            }

            return m_ret;
        }

        static R6 getNormalizedTwist(const R6 &twist)
        {
            double theta = twist.block<3, 1>(0, 0).norm();
            if (!NearZero(twist.norm()) && NearZero(theta))
                return twist.normalized();
            else
                return twist / theta;
        }

        static SE3 UnitZ()
        {
            state_space::R6 temp_twist;
            temp_twist << 0, 0, 1, 0, 0, 0;
            return SE3(temp_twist);
        };
        static SE3 UnitX()
        {
            state_space::R6 temp_twist;
            temp_twist << 1, 0, 0, 0, 0, 0;
            return SE3(temp_twist);
        };
        static SE3 UnitY()
        {
            state_space::R6 temp_twist;
            temp_twist << 0, 1, 0, 0, 0, 0;
            return SE3(temp_twist);
        };

        static inline bool isSE3(const SE_3 &transform)
        {
            return (SO3::isOrthogonal(transform.block<3, 3>(0, 0))) &&
                   transform.matrix().row(3).isApprox(Eigen::Vector4d::UnitW().transpose(),
                                                      Eigen::NumTraits<double>::dummy_precision());
        }

        static inline SE_3 projectToSE3(const SE_3 &transform)
        {
            SE_3 temp;
            temp << SO3::projectToSO3(transform.block<3, 3>(0, 0)), transform.block<3, 1>(0, 3),
                    0, 0, 0, 1;
            return temp;
        }

        friend std::ostream &operator<<(std::ostream &s, const SE3 &input)
        {
            s << input.pose_with_quaternion().transpose();
            return s;
        }
    };

}

#endif //NURSINGROBOT_SE3_HPP
