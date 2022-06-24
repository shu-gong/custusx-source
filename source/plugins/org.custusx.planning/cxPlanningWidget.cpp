/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#include <iostream>
#include "cxPlanningWidget.h"
#include "./include/planner/InsertPlanner.hpp"

namespace cx
{

PlanningWidget::PlanningWidget(QWidget* parent) :QWidget(parent), mVerticalLayout(new QVBoxLayout(this))
{
    QPushButton *btn = new QPushButton("planning test", this);
    mVerticalLayout->addWidget(btn);
    connect(btn,&QPushButton::clicked,this,&PlanningWidget::startPlanning);

}

PlanningWidget::~PlanningWidget()
{
}

void PlanningWidget::startPlanning()
{
    qDebug()<<"开始规划了";

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
        //solution = planner_ptr->solve(start_state.translationPart(), goal_state.translationPart());
        Eigen::Vector3d start{-0.044938, -0.15572, -0.241432};
        Eigen::Vector3d start_near_before{-0.0448, -0.15572, -0.2413};
        Eigen::Vector3d goal{-0.0379019, -0.158161, -0.235144};
        auto path = planner_ptr->solve(start, start_near_before, goal);
        if(!path.empty()){
            for(const auto& item: path){
                std::cout<<item.transpose()<<std::endl;
            }
        }
    }catch(std::invalid_argument & e){
        std::cout<<e.what()<<std::endl;
    }
//#endif



}

QString PlanningWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Planning plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}
} /* namespace cx */
