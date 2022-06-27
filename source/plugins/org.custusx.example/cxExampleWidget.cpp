/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxExampleWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

namespace cx
{

ExampleWidget::ExampleWidget(QWidget* parent) :
    QWidget(parent),
    mVerticalLayout(new QVBoxLayout(this))
{
    this->setObjectName("ExampleWidget");
    this->setWindowTitle("Example");
    this->setWhatsThis(this->defaultWhatsThis());

 QPushButton *btn = new QPushButton("example test", this);
 mVerticalLayout->addWidget(btn);
 connect(btn,&QPushButton::clicked,this,&ExampleWidget::startExample);

}

ExampleWidget::~ExampleWidget()
{
}
void ExampleWidget::startExample()
{
 qDebug()<<"开始规划了";
 cv::VideoCapture cap;              // Open input
 //cap.open("/home/shu/HamlynDatasetShort/f7phantom/f7_dynamic_deint_L.avi");
 cap.open(0);

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
QString ExampleWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Example plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}



} /* namespace cx */
