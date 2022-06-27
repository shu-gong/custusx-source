/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#include <iostream>
#include "cxVslamWidget.h"
#include <QVBoxLayout>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "Modules/Common/System.h"

namespace cx
{

VslamWidget::VslamWidget(QWidget* parent) :QWidget(parent), mVerticalLayout(new QVBoxLayout(this))
{
    this->setObjectName("VslamWidget");
    this->setWindowTitle("Vslam");

    QPushButton *btn = new QPushButton("vslam test", this);
    mVerticalLayout->addWidget(btn);
    connect(btn,&QPushButton::clicked,this,&VslamWidget::startVslam);

}

VslamWidget::~VslamWidget()
{
}

void VslamWidget::startVslam()
{
    qDebug()<<"开始规划了";
    cv::VideoCapture cap;              // Open input
    cap.open("/home/shu/HamlynDatasetShort/f7phantom/f7_dynamic_deint_L.avi");
    if(!cap.isOpened()){
     std::cout << "Error opening video stream or file" << std::endl;
    }
    while(1){
     cv::Mat frame;
     // Capture frame-by-frame
     cap >> frame;
     // If the frame is empty, break immediately
     if (frame.empty())
      break;
     // Display the resulting frame
     cv::imshow( "Frame", frame );
     // Press  ESC on keyboard to exit
     char c=(char)cv::waitKey(25);
     if(c==27)
      break;
    }
    // When everything done, release the video capture object
    cap.release();

}

QString VslamWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Vslam plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}
} /* namespace cx */
