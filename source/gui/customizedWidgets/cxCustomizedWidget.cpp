/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.

Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.

CustusX is released under a BSD 3-Clause license.

See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxCustomizedWidget.h"

#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "cxFrameForest.h"
#include "cxData.h"
#include "cxPatientModelService.h"
#include <QDebug>

#include "cxMesh.h"
#include "cxData.h"
#include "cxImage.h"
#include "cxDataLocations.h"
#include "cxLogicManager.h"
#include "cxPatientModelService.h"
#include <vtkImageData.h>
#include <vtkPolyData.h>
#include "cxForwardDeclarations.h"

namespace cx
{

CustomizedWidget::CustomizedWidget(PatientModelServicePtr patientService, QWidget* parent) :
  BaseWidget(parent, "CustomizedWidget", "CustomizedWidget"),
  mPatientService(patientService),
  mVerticalLayout(new QVBoxLayout(this))
{
    QPushButton *btn = new QPushButton("Start", this);
    mVerticalLayout->addWidget(btn);
    connect(btn,&QPushButton::clicked,this,&CustomizedWidget::startPlanning);
}

void CustomizedWidget::startPlanning(){
    qDebug()<<"Don't Panic!";
    cx::DataPtr tube = mPatientService->getData("Thorax__1_0__B30f_4_20220421T163621_tubes1");
    cx::MeshPtr tubeMesh = boost::dynamic_pointer_cast<cx::Mesh>(tube);
    vtkPolyDataPtr tubeDataPtr = tubeMesh->getVtkPolyData();
    qDebug()<<tubeDataPtr->GetPiece();
}

}
