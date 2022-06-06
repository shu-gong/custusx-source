/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXNODEPLUGINACTIVATOR_H_
#define CXNODEPLUGINACTIVATOR_H_

#include <ctkPluginActivator.h>
#include "boost/shared_ptr.hpp"

namespace cx
{

typedef boost::shared_ptr<class NodeGUIExtenderService> NodeGUIExtenderServicePtr;
typedef boost::shared_ptr<class RegisteredService> RegisteredServicePtr;

/**
 * Activator for the example plugin
 *
 * \ingroup org_custusx_example
 *
 * \date 2014-04-15
 * \author Christian Askeland
 */
class NodePluginActivator :  public QObject, public ctkPluginActivator
{
	Q_OBJECT
	Q_INTERFACES(ctkPluginActivator)
	Q_PLUGIN_METADATA(IID "org_custusx_node")

public:

	NodePluginActivator();
	~NodePluginActivator();

	void start(ctkPluginContext* context);
	void stop(ctkPluginContext* context);

private:
	RegisteredServicePtr mRegistration;
};

} // namespace cx

#endif /* CXNODEPLUGINACTIVATOR_H_ */
