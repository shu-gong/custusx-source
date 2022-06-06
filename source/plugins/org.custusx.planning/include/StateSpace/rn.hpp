//
// Created by xcy on 2020/12/16.
//

#ifndef NURSINGROBOT_RN_HPP
#define NURSINGROBOT_RN_HPP

#include "../StateSpace/StateSpace.hpp"
#include "../macros/class_forward.h"
namespace state_space {

    DONT_ALIGN_CLASS_STL_FORWARD(Rn)

    class Rn : private virtual StateSpace<Rn> {
    protected:
        unsigned int _dimensions_;
        Eigen::VectorXd _data_;
    public:

        explicit Rn(unsigned int dimensions = 3)
        {
            this->_data_.resize(dimensions);
            this->_data_.setZero();
            this->_dimensions_ = dimensions;
        };

        explicit Rn(const Eigen::VectorXd &data)
                : _data_(data)
        {
            this->_dimensions_ = data.size();
        };

        explicit Rn(const void *data_ptr, unsigned int dimensions)
        {
            this->_data_.resize(dimensions);
            memcpy(_data_.data(), data_ptr, dimensions * sizeof(double));
            this->_dimensions_ = dimensions;
        }

        explicit Rn(const std::vector<double> &vector_input)
        {
            this->_dimensions_ = vector_input.size();
            this->_data_.resize(_dimensions_);
            memcpy(this->_data_.data(), vector_input.data(), _dimensions_ * sizeof(double));
        }

        ~Rn() override = default;

        Eigen::VectorXd Vector() const
        { return _data_; };

        Rn operator+(const Rn &input) const override
        {
            return Rn(this->Vector() + input.Vector());
        };

        Rn operator-(const Rn &input) const override
        {
            return Rn(this->Vector() - input.Vector());
        };

        Rn operator*(double s) const override
        {
            return Rn(this->Vector() * s);
        };

        friend Rn operator*(double s, const Rn &input)
        {
            return input * s;
        };

        Rn operator()(double theta) const override
        {
            return Rn(this->Vector().normalized() * theta);
        };

        double &operator[](const long index)
        {
            return this->_data_[index];
        };

        double operator[](const size_t index) const
        {
            return this->_data_[index];
        };

        bool operator==(const Rn &other) const override
        {
            return _data_ == other._data_;
        }

        unsigned int Dimensions() const override
        {
            return _dimensions_;
        };

        const double *data() const override
        {
            return this->_data_.data();
        };


        Rn inverse() const override
        {
            return Rn(-1 * this->Vector());
        };

        Rn random(std::default_random_engine &randomEngine, const Eigen::MatrixX2d *bounds_ptr) const override
        {
            Eigen::VectorXd result(_dimensions_);
            std::uniform_real_distribution<double> x_distribution(0, 1);
            if (bounds_ptr != nullptr) {
                for (int i = 0; i < this->_dimensions_; ++i) {
                    result[i] = bounds_ptr->col(1)[i] +
                                x_distribution(randomEngine) * (bounds_ptr->col(0)[i] - bounds_ptr->col(1)[i]);
                }
            } else {
                //[-1,1]
                for (int i = 0; i < this->_dimensions_; ++i) {
                    result[i] = -1 + x_distribution(randomEngine) * 2;
                }
            }
            return Rn(result);
        };

        double norm() const override
        {
            return (this->_data_.norm());
        };

        static Rn Zero(unsigned int dimensions = 3)
        {
            return Rn(dimensions);
        }

        double distance(const Rn &to) const override
        {
            return (*this - to).norm();
        };

        bool isValid(const Eigen::MatrixX2d *bounds_ptr) const
        {
            return !(((this->_data_ - bounds_ptr->col(0)).array() > 0).any() ||
                     ((this->_data_ - bounds_ptr->col(1)).array() < 0).any());
        };

        bool isValid(const Eigen::VectorXd &upper_bound, const Eigen::VectorXd &lower_bound) const
        {
            return !(((this->_data_ - upper_bound).array() > 0).any() ||
                     ((this->_data_ - lower_bound).array() < 0).any());
        };

        friend std::ostream &operator<<(std::ostream &s, const Rn &input)
        {
            s << input._data_.transpose();
            return s;
        }
    };

}


#endif //NURSINGROBOT_RN_HPP
