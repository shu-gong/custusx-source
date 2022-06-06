/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXCONTROLWIDGET_H_
#define CXCONTROLWIDGET_H_

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

class QVBoxLayout;
class QDial;
class QSlider;
class QPushButton;

namespace cx
{

/**
 * Widget for use in the plugin control
 *
 * \ingroup org_custusx_control
 *
 * \date 2014-05-02
 * \author Christian Askeland
 */
class ControlWidget : public QWidget
{
	Q_OBJECT
public:
	ControlWidget(QWidget* parent = 0);
	virtual ~ControlWidget();


private:
	QString defaultWhatsThis() const;
	QVBoxLayout*  mVerticalLayout;

};

} /* namespace cx */

#endif /* CXCONTROLWIDGET_H_ */
