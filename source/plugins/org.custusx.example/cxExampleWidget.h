/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXEXAMPLEWIDGET_H_
#define CXEXAMPLEWIDGET_H_

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
 * Widget for use in the plugin example
 *
 * \ingroup org_custusx_example
 *
 * \date 2014-05-02
 * \author Christian Askeland
 */
class ExampleWidget : public QWidget
{
	Q_OBJECT
public:
	ExampleWidget(QWidget* parent = 0);
	virtual ~ExampleWidget();
    void retranslateUi(QWidget *Widget);

protected:
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_10;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_11;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_12;
    QPushButton *pushButton_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox_7;
    QSpinBox *spinBox_8;
    QSpinBox *spinBox_9;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLCDNumber *lcdNumber_3;
    QLabel *label_5;
    QLCDNumber *lcdNumber_2;
    QLabel *label_4;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLCDNumber *lcdNumber_4;
    QLabel *label_8;
    QLCDNumber *lcdNumber_5;
    QLabel *label_9;
    QLCDNumber *lcdNumber_6;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;

private:
	QString defaultWhatsThis() const;
	QVBoxLayout*  mVerticalLayout;

};

} /* namespace cx */

#endif /* CXEXAMPLEWIDGET_H_ */
