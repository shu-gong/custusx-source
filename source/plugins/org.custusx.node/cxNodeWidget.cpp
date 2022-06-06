/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxNodeWidget.h"
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

NodeWidget::NodeWidget(QWidget* parent) :QWidget(parent), mVerticalLayout(new QVBoxLayout(this))
{
    this->setObjectName("NodeWidget");
    this->setWindowTitle("Node");
    this->setWhatsThis(this->defaultWhatsThis());

   // mVerticalLayout->addWidget(new QLabel("Hello Plugin!"));

//    this = new QWidget(Widget);
//    this->setObjectName(QString::fromUtf8("this"));
//    this->setGeometry(QRect(60, 70, 431, 691));
    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);

    mVerticalLayout->addWidget(label);

    checkBox_10 = new QCheckBox(this);
    checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));

    mVerticalLayout->addWidget(checkBox_10);

    checkBox_11 = new QCheckBox(this);
    checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));

    mVerticalLayout->addWidget(checkBox_11);

    checkBox_12 = new QCheckBox(this);
    checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));

    mVerticalLayout->addWidget(checkBox_12);

    horizontalLayout_13 = new QHBoxLayout();
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
    label_10 = new QLabel(this);
    label_10->setObjectName(QString::fromUtf8("label_10"));

    horizontalLayout_13->addWidget(label_10);

    doubleSpinBox_10 = new QDoubleSpinBox(this);
    doubleSpinBox_10->setObjectName(QString::fromUtf8("doubleSpinBox_10"));

    horizontalLayout_13->addWidget(doubleSpinBox_10);


    mVerticalLayout->addLayout(horizontalLayout_13);

    horizontalLayout_14 = new QHBoxLayout();
    horizontalLayout_14->setSpacing(6);
    horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
    label_11 = new QLabel(this);
    label_11->setObjectName(QString::fromUtf8("label_11"));

    horizontalLayout_14->addWidget(label_11);

    doubleSpinBox_11 = new QDoubleSpinBox(this);
    doubleSpinBox_11->setObjectName(QString::fromUtf8("doubleSpinBox_11"));

    horizontalLayout_14->addWidget(doubleSpinBox_11);


    mVerticalLayout->addLayout(horizontalLayout_14);

    horizontalLayout_15 = new QHBoxLayout();
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
    label_12 = new QLabel(this);
    label_12->setObjectName(QString::fromUtf8("label_12"));

    horizontalLayout_15->addWidget(label_12);

    doubleSpinBox_12 = new QDoubleSpinBox(this);
    doubleSpinBox_12->setObjectName(QString::fromUtf8("doubleSpinBox_12"));

    horizontalLayout_15->addWidget(doubleSpinBox_12);


    mVerticalLayout->addLayout(horizontalLayout_15);

    pushButton_4 = new QPushButton(this);
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
    pushButton_4->setEnabled(true);
    pushButton_4->setLayoutDirection(Qt::LeftToRight);

    mVerticalLayout->addWidget(pushButton_4);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setFont(font);

    mVerticalLayout->addWidget(label_2);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    spinBox_3 = new QSpinBox(this);
    spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

    horizontalLayout->addWidget(spinBox_3);

    spinBox = new QSpinBox(this);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));

    horizontalLayout->addWidget(spinBox);

    spinBox_2 = new QSpinBox(this);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

    horizontalLayout->addWidget(spinBox_2);

    pushButton = new QPushButton(this);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    horizontalLayout->addWidget(pushButton);


    mVerticalLayout->addLayout(horizontalLayout);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    spinBox_4 = new QSpinBox(this);
    spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

    horizontalLayout_2->addWidget(spinBox_4);

    spinBox_5 = new QSpinBox(this);
    spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

    horizontalLayout_2->addWidget(spinBox_5);

    spinBox_6 = new QSpinBox(this);
    spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));

    horizontalLayout_2->addWidget(spinBox_6);

    pushButton_2 = new QPushButton(this);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    horizontalLayout_2->addWidget(pushButton_2);


    mVerticalLayout->addLayout(horizontalLayout_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    spinBox_7 = new QSpinBox(this);
    spinBox_7->setObjectName(QString::fromUtf8("spinBox_7"));

    horizontalLayout_3->addWidget(spinBox_7);

    spinBox_8 = new QSpinBox(this);
    spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));

    horizontalLayout_3->addWidget(spinBox_8);

    spinBox_9 = new QSpinBox(this);
    spinBox_9->setObjectName(QString::fromUtf8("spinBox_9"));

    horizontalLayout_3->addWidget(spinBox_9);

    pushButton_3 = new QPushButton(this);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

    horizontalLayout_3->addWidget(pushButton_3);


    mVerticalLayout->addLayout(horizontalLayout_3);

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setFont(font);

    mVerticalLayout->addWidget(label_3);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    label_6 = new QLabel(this);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    horizontalLayout_5->addWidget(label_6);

    lcdNumber_3 = new QLCDNumber(this);
    lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));

    horizontalLayout_5->addWidget(lcdNumber_3);

    label_5 = new QLabel(this);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    horizontalLayout_5->addWidget(label_5);

    lcdNumber_2 = new QLCDNumber(this);
    lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));

    horizontalLayout_5->addWidget(lcdNumber_2);

    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    horizontalLayout_5->addWidget(label_4);

    lcdNumber = new QLCDNumber(this);
    lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
    lcdNumber->setProperty("intValue", QVariant(65));

    horizontalLayout_5->addWidget(lcdNumber);


    mVerticalLayout->addLayout(horizontalLayout_5);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
    label_7 = new QLabel(this);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    horizontalLayout_6->addWidget(label_7);

    lcdNumber_4 = new QLCDNumber(this);
    lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));

    horizontalLayout_6->addWidget(lcdNumber_4);

    label_8 = new QLabel(this);
    label_8->setObjectName(QString::fromUtf8("label_8"));

    horizontalLayout_6->addWidget(label_8);

    lcdNumber_5 = new QLCDNumber(this);
    lcdNumber_5->setObjectName(QString::fromUtf8("lcdNumber_5"));

    horizontalLayout_6->addWidget(lcdNumber_5);

    label_9 = new QLabel(this);
    label_9->setObjectName(QString::fromUtf8("label_9"));

    horizontalLayout_6->addWidget(label_9);

    lcdNumber_6 = new QLCDNumber(this);
    lcdNumber_6->setObjectName(QString::fromUtf8("lcdNumber_6"));
    lcdNumber_6->setProperty("intValue", QVariant(65));

    horizontalLayout_6->addWidget(lcdNumber_6);


    mVerticalLayout->addLayout(horizontalLayout_6);

    label_13 = new QLabel(this);
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setFont(font);

    mVerticalLayout->addWidget(label_13);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    pushButton_7 = new QPushButton(this);
    pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

    horizontalLayout_4->addWidget(pushButton_7);

    pushButton_6 = new QPushButton(this);
    pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

    horizontalLayout_4->addWidget(pushButton_6);

    pushButton_5 = new QPushButton(this);
    pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

    horizontalLayout_4->addWidget(pushButton_5);


    mVerticalLayout->addLayout(horizontalLayout_4);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    pushButton_8 = new QPushButton(this);
    pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

    horizontalLayout_7->addWidget(pushButton_8);

    pushButton_9 = new QPushButton(this);
    pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

    horizontalLayout_7->addWidget(pushButton_9);

    pushButton_10 = new QPushButton(this);
    pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

    horizontalLayout_7->addWidget(pushButton_10);


    mVerticalLayout->addLayout(horizontalLayout_7);

    horizontalLayout_8 = new QHBoxLayout();
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    pushButton_11 = new QPushButton(this);
    pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

    horizontalLayout_8->addWidget(pushButton_11);

    pushButton_12 = new QPushButton(this);
    pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

    horizontalLayout_8->addWidget(pushButton_12);

    pushButton_13 = new QPushButton(this);
    pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));

    horizontalLayout_8->addWidget(pushButton_13);


    mVerticalLayout->addLayout(horizontalLayout_8);

    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    pushButton_14 = new QPushButton(this);
    pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));

    horizontalLayout_9->addWidget(pushButton_14);

    pushButton_15 = new QPushButton(this);
    pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));

    horizontalLayout_9->addWidget(pushButton_15);

    pushButton_16 = new QPushButton(this);
    pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));

    horizontalLayout_9->addWidget(pushButton_16);


    mVerticalLayout->addLayout(horizontalLayout_9);

    this->raise();
    pushButton_9->raise();
    pushButton_6->raise();

    retranslateUi(this);

}

NodeWidget::~NodeWidget()
{
}

void NodeWidget:: retranslateUi(QWidget *Widget)
{
    Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
    label->setText(QApplication::translate("Widget", "System Setup", 0));
    checkBox_10->setText(QApplication::translate("Widget", "Connect TSS", 0));
    checkBox_11->setText(QApplication::translate("Widget", "Connect RCM", 0));
    checkBox_12->setText(QApplication::translate("Widget", "Teleoperation", 0));
    label_10->setText(QApplication::translate("Widget", "Throat Size(mm)", 0));
    label_11->setText(QApplication::translate("Widget", "Motion Scale", 0));
    label_12->setText(QApplication::translate("Widget", "Pressure (kPa)", 0));
    pushButton_4->setText(QApplication::translate("Widget", "set", 0));
    label_2->setText(QApplication::translate("Widget", "Move to Position", 0));
    pushButton->setText(QApplication::translate("Widget", "MOT", 0));
    pushButton_2->setText(QApplication::translate("Widget", "XYZ", 0));
    pushButton_3->setText(QApplication::translate("Widget", "ABL", 0));
    label_3->setText(QApplication::translate("Widget", "TSS State", 0));
    label_6->setText(QApplication::translate("Widget", "A", 0));
    label_5->setText(QApplication::translate("Widget", "B", 0));
    label_4->setText(QApplication::translate("Widget", "L", 0));
    label_7->setText(QApplication::translate("Widget", "X", 0));
    label_8->setText(QApplication::translate("Widget", "Y", 0));
    label_9->setText(QApplication::translate("Widget", "Z", 0));
    label_13->setText(QApplication::translate("Widget", "TSS Control", 0));
    pushButton_7->setText(QApplication::translate("Widget", "X+", 0));
    pushButton_6->setText(QApplication::translate("Widget", "Y+", 0));
    pushButton_5->setText(QApplication::translate("Widget", "Z+", 0));
    pushButton_8->setText(QApplication::translate("Widget", "X-", 0));
    pushButton_9->setText(QApplication::translate("Widget", "Y-", 0));
    pushButton_10->setText(QApplication::translate("Widget", "Z-", 0));
    pushButton_11->setText(QApplication::translate("Widget", "A+", 0));
    pushButton_12->setText(QApplication::translate("Widget", "B+", 0));
    pushButton_13->setText(QApplication::translate("Widget", "L+", 0));
    pushButton_14->setText(QApplication::translate("Widget", "A-", 0));
    pushButton_15->setText(QApplication::translate("Widget", "B-", 0));
    pushButton_16->setText(QApplication::translate("Widget", "L-", 0));
}

QString NodeWidget::defaultWhatsThis() const
{
  return "<html>"
      "<h3>Node plugin.</h3>"
      "<p>Used for developers as a starting points for developing a new plugin</p>"
      "</html>";
}
} /* namespace cx */
