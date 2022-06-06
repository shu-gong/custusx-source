#include <iostream>
//#define VTK_
#include "planner/InsertPlanner.hpp"

int main() {

    planner::InsertBounds bounds(3,2);
    bounds << Eigen::Vector3d{0.2, 0.2, 0.2},
            Eigen::Vector3d{-0.2, -0.2, -0.2};
    auto start_state = planner::randomState<state_space::InsertState>(6, &bounds);
    auto goal_state = planner::randomState<state_space::InsertState>(6, &bounds);

    planner::InsertRRTPtr planner_ptr;
    planner_ptr.reset(new planner::InsertPlanner());

    planner_ptr->constructPlan(start_state, goal_state);

    std::vector<state_space::InsertState> path;
    clock_t before{clock()};
    if (planner_ptr->planning()) {
        std::cout<<"time: "<<static_cast<double>((clock()-before))/CLOCKS_PER_SEC<<""
                                                                                   "s"<<std::endl;
        path = planner_ptr->GetPath();
        for(const auto & item: path){
            std::cout<<item.translationPart().transpose()<<std::endl;
        }
    }
//#ifdef VTK_
    vtkPolyDataPtr solution;
    try{
        solution = planner_ptr->solve(start_state.translationPart(), goal_state.translationPart());
    }catch(std::invalid_argument & e){
        std::cout<<e.what()<<std::endl;
    }
//#endif
}
