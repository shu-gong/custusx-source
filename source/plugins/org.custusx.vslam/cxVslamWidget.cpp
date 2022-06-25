/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#include <iostream>
#include "cxVslamWidget.h"
namespace cx
{

VslamWidget::VslamWidget(QWidget* parent) :QWidget(parent), mVerticalLayout(new QVBoxLayout(this))
{
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
    /*
    cv::VideoCapture cap;
    cap.open("/home/shu/HamlynDatasetShort/f7phantom/f7_dynamic_deint_L.avi");
    // Create SLAM system. It initializes all system threads and gets ready to
    // process frames.
    defSLAM::System SLAM("/home/shu/Gitee/defslam/custusx-position/Vocabulary/ORBvoc.txt", "/home/shu/HamlynDatasetShort/f7phantom/hamlyn.yaml", true);

    uint i(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (cap.isOpened())
    {
        cv::Mat imLeft;
        cap >> imLeft;

        if (imLeft.empty())
        {
            cerr << endl
                 << "Failed to load image at: " << to_string(i) << endl;
            return 1;
        }

        SLAM.TrackMonocular(imLeft, i);
        i++;
    }

    SLAM.Shutdown();
*/
}

QString VslamWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Vslam plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}
} /* namespace cx */
