/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxControlWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QApplication>


namespace cx
{

ControlWidget::ControlWidget(QWidget* parent) :QWidget(parent), mVerticalLayout(new QVBoxLayout(this))
{
    this->setObjectName("ControlWidget");
    this->setWindowTitle("Control");
    this->setWhatsThis(this->defaultWhatsThis());

    mVerticalLayout->addWidget(new QLabel("Hello Plugin!"));

//    this = new QWidget(Widget);
//    this->setObjectName(QString::fromUtf8("this"));
//    this->setGeometry(QRect(60, 70, 431, 691));

}

ControlWidget::~ControlWidget()
{
}


QString ControlWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Control plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}
} /* namespace cx */
