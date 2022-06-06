/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxControlPluginActivator.h"

#include <QtPlugin>
#include <iostream>

#include "cxControlGUIExtenderService.h"
#include "cxRegisteredService.h"

namespace cx
{

ControlPluginActivator::ControlPluginActivator()
{
	std::cout << "Created ControlPluginActivator" << std::endl;
}

ControlPluginActivator::~ControlPluginActivator()
{}

void ControlPluginActivator::start(ctkPluginContext* context)
{
	mRegistration = RegisteredService::create<ControlGUIExtenderService>(context, GUIExtenderService_iid);
}

void ControlPluginActivator::stop(ctkPluginContext* context)
{
	mRegistration.reset();
	Q_UNUSED(context);
}

} // namespace cx



