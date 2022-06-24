/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#ifndef CXPLANNINGWIDGET_H_
#define CXPLANNINGWIDGET_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QDebug>
//#define VTK_

//#include "cxPlanningWidget.h"


class QVBoxLayout;
class QPushButton;

namespace cx
{

/**
 * Widget for use in the plugin planning
 *
 * \ingroup org_custusx_planning
 *
 * \date 2014-05-02
 * \author Christian Askeland
 */
class PlanningWidget : public QWidget
{
    Q_OBJECT
public:
	PlanningWidget(QWidget* parent = 0);
	virtual ~PlanningWidget();

private:
    QString defaultWhatsThis() const;
    QVBoxLayout*  mVerticalLayout;

private slots:
    void startPlanning();

};

} /* namespace cx */

#endif /* CXPLANNINGWIDGET_H_ */
