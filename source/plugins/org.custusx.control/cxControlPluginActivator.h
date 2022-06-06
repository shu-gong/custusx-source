/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXCONTROLPLUGINACTIVATOR_H_
#define CXCONTROLPLUGINACTIVATOR_H_

#include <ctkPluginActivator.h>
#include "boost/shared_ptr.hpp"

namespace cx
{

typedef boost::shared_ptr<class ControlGUIExtenderService> ControlGUIExtenderServicePtr;
typedef boost::shared_ptr<class RegisteredService> RegisteredServicePtr;

/**
 * Activator for the control plugin
 *
 * \ingroup org_custusx_control
 *
 * \date 2014-04-15
 * \author Christian Askeland
 */
class ControlPluginActivator :  public QObject, public ctkPluginActivator
{
	Q_OBJECT
	Q_INTERFACES(ctkPluginActivator)
	Q_PLUGIN_METADATA(IID "org_custusx_control")

public:

	ControlPluginActivator();
	~ControlPluginActivator();

	void start(ctkPluginContext* context);
	void stop(ctkPluginContext* context);

private:
	RegisteredServicePtr mRegistration;
};

} // namespace cx

#endif /* CXCONTROLPLUGINACTIVATOR_H_ */
