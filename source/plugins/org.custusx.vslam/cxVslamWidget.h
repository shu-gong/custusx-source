/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#ifndef CXVSLAMWIDGET_H_
#define CXVSLAMWIDGET_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QDebug>

class QVBoxLayout;
class QPushButton;

namespace cx
{

/**
 * Widget for use in the plugin vslam
 *
 * \ingroup org_custusx_vslam
 *
 * \date 2014-05-02
 * \author Christian Askeland
 */
class VslamWidget : public QWidget
{
    Q_OBJECT
public:
	VslamWidget(QWidget* parent = 0);
	virtual ~VslamWidget();

private:
    QString defaultWhatsThis() const;
    QVBoxLayout*  mVerticalLayout;

private slots:
    void startVslam();

};

} /* namespace cx */

#endif /* CXVSLAMWIDGET_H_ */
