#ifndef INSERTPLANNER_INSERTSPACE_HPP
#define INSERTPLANNER_INSERTSPACE_HPP

#include "SE3.hpp"
#include "planner/Planner.hpp"

namespace state_space {
    struct CircParams {
    public:
        CircParams(double l_, double r_, double theta_) : l(l_), r(r_), theta(theta_) {

        };

        double l, r, theta;
    };

    class InsertState : public SE3 {
    public:
        explicit InsertState() : SE3(6) {

        };

        ~InsertState() override = default;

        InsertState(const InsertState &a) : SE3(a.Vector()) {};

        explicit InsertState(const double *data_ptr, unsigned int dimensions) : SE3(data_ptr, dimensions) {};

        explicit InsertState(const R6 &twist) : SE3(twist) {};

        explicit InsertState(const Eigen::Matrix<double, 7, 1> &pose_with_quaternion) : SE3(pose_with_quaternion) {};

        explicit InsertState(const Eigen::Affine3d &transformation_matrix) : SE3(transformation_matrix) {};

        explicit InsertState(const SE_3 &transformation_matrix) : SE3(transformation_matrix) {};

        explicit InsertState(const SE3 &SE3_element) : SE3(SE3_element) {};

        explicit InsertState(const Eigen::Vector3d &translation_part) : InsertState(SO3::Zero(), translation_part) {};

        explicit InsertState(const SO3 &SO3_part, const R3 &translation_part) : SE3(SO3_part, translation_part) {};

        explicit InsertState(const std::vector<double> &vector_input) : SE3(vector_input) {};

        InsertState &operator=(const InsertState &input) {
            StateSpace<SE3>::operator=(input);
            this->_twist_3d_ = input._twist_3d_;
            this->SE3_matrix_ = input.SE3_matrix_;
        }

    public:
        static CircParams solveParams(const state_space::InsertState &from, const state_space::InsertState &to) {
            R3 p = (to - from).translationPart();
            double temp{sqrt(p[0] * p[0] + p[1] * p[1])};
            double r{0.5 * p.array().pow(2).sum() / temp};
            return {r * std::atan2(p[2], r - temp), r, std::atan2(p[0], -p[1])};
        };
        static double curvature;
    };

}
namespace planner {
    template<>
    state_space::InsertState
    extend(const state_space::InsertState &source, const state_space::InsertState &target, double extend_length) {
        state_space::CircParams path_params = state_space::InsertState::solveParams(source, target);
        auto result = source + state_space::InsertState(
                state_space::R6(std::vector<double>{0., 0., path_params.theta, 0., 0., 0.}.data()));
        result = result + state_space::InsertState(
                state_space::R6(std::vector<double>{path_params.l / (extend_length * path_params.r), 0., 0.,
                                                    0., 0., path_params.l / extend_length}.data()));
        return state_space::InsertState{result};
    }

    template<>
    double distance(const state_space::InsertState &from, const state_space::InsertState &to) {
        /*if(from == to)
            return 0.;
        state_space::CircParams path_params = state_space::InsertState::solveParams(from, to);
        return  (path_params.theta >= 0 && path_params.r >= 1./state_space::InsertState::curvature) ?
        std::abs(path_params.l) : std::numeric_limits<double>::max();*/
        return (from.translationPart() - to.translationPart()).norm();
    };

    template<>
    state_space::InsertState randomState(int dimensions, const Eigen::MatrixX2d *bounds_ptr) {
        auto translation_part = randomState<state_space::Rn>(3, bounds_ptr);
        return state_space::InsertState{Eigen::Vector3d{translation_part.Vector()}};
    }
}


#endif //INSERTPLANNER_INSERTSPACE_HPP
