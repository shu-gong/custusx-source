#ifndef INSERTPLANNER_INSERTRRT_HPP
#define INSERTPLANNER_INSERTRRT_HPP

#include "../planner/Tree.hpp"
#include "../planner/RRT.hpp"
#include "../StateSpace/insertSpace.hpp"

#include "vtkForwardDeclarations.h"
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

//#define VTK_

//#ifdef VTK_

//#endif

double state_space::InsertState::curvature{20.};

namespace planner{

    static bool isPathValid(const state_space::InsertState& from, const state_space::InsertState& to){
        if(from==to) return true;
        state_space::CircParams params = state_space::InsertState::solveParams(from, to);
        return (params.theta >= 0. && params.r >= 1./state_space::InsertState::curvature) || params.l < 1e-14;
    }
    static void toArray(const state_space::InsertState& current, double * query_data) {
        memcpy(query_data, current.translationPart().data(), sizeof(double) * 3);
    }

    typedef std::shared_ptr<Tree<state_space::InsertState, flann::L2_3D<double>>> InsertTreePtr;
    typedef PLAN_REQUEST<state_space::InsertState, flann::L2_3D<double>> InsertPlanRequest;
    typedef Eigen::MatrixX2d InsertBounds;

    class InsertPlanner : public RRT<state_space::InsertState, flann::L2_3D<double>>{
    public:
        InsertPlanner(const InsertPlanner&) = delete;
        InsertPlanner &operator=(const InsertPlanner&) = delete;

        explicit InsertPlanner()
        : RRT<state_space::InsertState, flann::L2_3D<double>>(3, nullptr, toArray){
            this->_state_validate_func = isPathValid;
            auto bounds = new InsertBounds(3,2);
            *bounds << Eigen::Vector3d{0.2, 0.2, 0.2},
                    Eigen::Vector3d{-0.2, -0.2, -0.2};
            this->setSampleBounds(bounds);
        };

        ~InsertPlanner() override = default;

    protected:
        double time_interval{1.};

    public:
        void setTimeInterval(double interval){
          time_interval = interval;
        };

        double getTimeInterval() const{
            return time_interval;
        }

        std::string getName() const override{
            return "Insert_RRT";
        }

        std::vector<state_space::InsertState> GetPath() override{
            auto result = RRT::GetPath();
            result.erase(result.end() - 1);
            return result;
        }
        using RRT::constructPlan;
        void constructPlan(const state_space::InsertState& start_state, const state_space::InsertState& goal_state){
            RRT::constructPlan(InsertPlanRequest (start_state, goal_state, 2,
                                                  1.,false,0.001,0.25));
        }

        std::vector<Eigen::Vector3d> solve(const Eigen::Vector3d& start, const Eigen::Vector3d& start_near,
                                           const Eigen::Vector3d& goal){
            std::vector<Eigen::Vector3d> positions;
            // compute orientation for z-axis
            constructPlan(state_space::InsertState{orientationZ( start - start_near),start}, state_space::InsertState{goal});
            if (planning()) {
                std::vector<state_space::InsertState> path = GetPath();
                for (int i = 0; i < path.size() - 1; i++) {
                    auto signal_params = state_space::InsertState::solveParams(path[i], path[i + 1]);
                    double interval{0.};
                    while (interval < 1.) {
                        positions.emplace_back(planner::extend(path[i], path[i + 1], interval).translationPart());
                        interval += 0.1;
                    }
                }
            }
            return positions;
        }
        /**
         *
         * @param theta The current bending angle of the final segment
         * @param end The position of end w.r.t. base
         * @param end_near The position of one point near to the end w.r.t. base
         * @param goal The position of nodule w.r.t. base
         * @return True for rotate in positive anti-clockwise, otherwise false
         */
        static bool solveBendingDirection(double theta, const Eigen::Vector3d& end, const Eigen::Vector3d& end_near,
                                          const Eigen::Vector3d& goal){
            const auto R = orientationZ( end - end_near);
            Eigen::Vector3d orientated_vector = R.SO3Matrix() * (goal - end);
            return solveBendingDirection(theta, orientated_vector[0]);
        }

    protected:
        state_space::InsertState _sample() override{
            Eigen::Matrix<double, 1, 1> random;random.setRandom();
            auto  index = static_cast<std::size_t>(random.cwiseAbs()[0] * _tree_ptr->TreeSize());
            index = index == _tree_ptr->TreeSize() ? index - 1 : index;
            auto nearest_vertex_ = _tree_ptr->fetchState(index);
            auto random_state = planner::randomState<state_space::InsertState>(-1, _bounds_ptr);
            while(!isReachable(nearest_vertex_->state(), random_state)){
                random_state = planner::randomState<state_space::InsertState>(-1, _bounds_ptr);
            }
            return random_state;
        }
        static inline state_space::SO3 orientationZ(const Eigen::Vector3d& axis){
           auto direction = axis.normalized()  ;
           auto sign = Eigen::sign(axis.array());
           // consider a ZYX order
           double yaw = std::acos(direction.block<2, 1>(0 ,0).dot(Eigen::Vector2d::UnitX())) * sign[1];
           double pitch = std::acos(direction.dot(Eigen::Vector3d::UnitZ())) * sign[2];
           return state_space::SO3{ 0., pitch, yaw};
        }

        static inline int sgn(double d){
            const double eps = 1e-7;
            return d<-eps?-1:d>eps;
        }

        static inline bool solveBendingDirection(double theta, double x){
            int sign_Jx = sgn(-theta * std::sin(theta) - std::cos(theta) + 1.);
            int sign_theta = sgn(x) * sign_Jx;
            return sign_theta == 1.;
        }

    private:
        static bool isReachable(const state_space::InsertState& from, const state_space::InsertState& to){
            state_space::R3 p = (to - from).translationPart();
            double temp{sqrt(p[0] * p[0] + p[1] * p[1])};
            double r{0.5 * p.array().pow(2).sum() / temp};
            return r >= 1./ state_space::InsertState::curvature;
        }

#ifdef VTK_
    public:
        /**
         *
         * @param start start_position
         * @param end end_position
         * @return vtk lines;
         * @throw std::invalid_arguments
         */
        vtkPolyDataPtr solve(const Eigen::Vector3d & start, const Eigen::Vector3d & end){
            constructPlan(state_space::InsertState{start}, state_space::InsertState{end});
            if (planning()){
                std::vector<state_space::InsertState> path = GetPath();
                std::vector<Eigen::Vector3d> positions;
                for(int i=0; i< path.size() - 1; i++){
                    auto signal_params = state_space::InsertState::solveParams(path[i], path[i+1]);
                    double interval{0.};
                    while (interval < 1.){
                        positions.emplace_back(planner::extend(path[i], path[i+1], interval).translationPart());
                        interval += 0.1;
                    }
                }
                vtkPolyDataPtr retval = vtkPolyDataPtr::New();
                vtkPointsPtr points = vtkPointsPtr::New();
                vtkCellArrayPtr lines = vtkCellArrayPtr::New();
                int numberOfPositions = positions.size();
                for (int j = numberOfPositions - 1; j >= 0; j--)
                {
                    points->InsertNextPoint(positions[j](0),positions[j](1),positions[j](2));
                }
                for (int j = 0; j < numberOfPositions-1; j++)
                {
                    vtkIdType connection[2] = {j, j+1};
                    lines->InsertNextCell(2, connection);
                }
                retval->SetPoints(points);
                retval->SetLines(lines);
                return retval;
            }else{
                throw std::invalid_argument("Cannot plan a valid path");
            }
        }
#endif
    };

    typedef std::shared_ptr<InsertPlanner> InsertRRTPtr;
}




#endif //INSERTPLANNER_INSERTRRT_HPP
