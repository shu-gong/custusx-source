/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxNodePluginActivator.h"

#include <QtPlugin>
#include <iostream>

#include "cxNodeGUIExtenderService.h"
#include "cxRegisteredService.h"

namespace cx
{

NodePluginActivator::NodePluginActivator()
{
        std::cout << "Created NodePluginActivator" << std::endl;
}

NodePluginActivator::~NodePluginActivator()
{}

void NodePluginActivator::start(ctkPluginContext* context)
{
        mRegistration = RegisteredService::create<NodeGUIExtenderService>(context, GUIExtenderService_iid);
}

void NodePluginActivator::stop(ctkPluginContext* context)
{
	mRegistration.reset();
	Q_UNUSED(context);
}

} // namespace cx



