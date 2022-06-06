#ifndef CXCUSTOMIZEDWIDGET_H_
#define CXCUSTOMIZEDWIDGET_H_

#include "cxResourceWidgetsExport.h"

#include "cxBaseWidget.h"

#include <map>
#include <string>
#include <QWidget>
#include "cxForwardDeclarations.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QDebug>


class QVBoxLayout;
class QPushButton;


class QVBoxLayout;
class QPushButton;

class QTreeWidget;
class QTreeWidgetItem;
class QDomNode;

namespace cx
{

class CustomizedWidget : public BaseWidget
{
  Q_OBJECT
public:
  CustomizedWidget(PatientModelServicePtr patientService, QWidget* parent);
  ~CustomizedWidget() {}

private:
  PatientModelServicePtr mPatientService;
  QString defaultWhatsThis() const;
  QVBoxLayout*  mVerticalLayout;

private slots:
  void startPlanning();
};


}

#endif /* CXCUSTOMIZEDWIDGET_H_ */

