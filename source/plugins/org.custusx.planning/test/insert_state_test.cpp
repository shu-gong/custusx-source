#include "StateSpace/insertSpace.hpp"
#include "gtest/gtest.h"
#include "planner/InsertPlanner.hpp"

double state_space::InsertState::curvature{20.};
bool isPathValid(const state_space::InsertState& from, const state_space::InsertState& to){
    if(from==to) return true;
    state_space::CircParams params = state_space::InsertState::solveParams(from, to);
    return params.r >= 1./state_space::InsertState::curvature;
}
TEST(IS_TEST, SOLVE_TEST){
    state_space::InsertState start_state{planner::randomState<state_space::SE3>()};
    auto test_state = planner::randomState<state_space::InsertState>();
    auto end_state = planner::extend(start_state, test_state, 1.);
    EXPECT_NEAR((end_state.translationPart() - test_state.translationPart()).norm(), 0,1E-14);
}

TEST(IS_TEST, PLAN_TEST){
    planner::InsertBounds bounds(3,2);
    bounds << Eigen::Vector3d{0.2, 0.2, 0.2},
            Eigen::Vector3d{-0.2, -0.2, -0.2};
    auto start_state = planner::randomState<state_space::InsertState>(6, &bounds);
    auto goal_state = planner::randomState<state_space::InsertState>(6, &bounds);

    planner::InsertRRTPtr rrt_based_planner_ptr;
    rrt_based_planner_ptr.reset(new planner::InsertRRT());

    rrt_based_planner_ptr->constructPlan(start_state, goal_state);

    std::vector<state_space::InsertState> path;
    clock_t before{clock()};
    if (rrt_based_planner_ptr->planning()) {
        std::cout<<"time: "<<static_cast<double>((clock()-before))/CLOCKS_PER_SEC<<""
                                                                                   "s"<<std::endl;
        path = rrt_based_planner_ptr->GetPath();
        for(const auto & item: path){
            std::cout<<item.translationPart().transpose()<<std::endl;
        }
    }
    EXPECT_NEAR(planner::distance(path.back(), goal_state), 0, 1e-3);
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

