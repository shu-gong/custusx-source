/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxVslamPluginActivator.h"

#include <QtPlugin>
#include <iostream>

#include "cxVslamGUIExtenderService.h"
#include "cxRegisteredService.h"

namespace cx
{

VslamPluginActivator::VslamPluginActivator()
{
	std::cout << "Created VslamPluginActivator" << std::endl;
}

VslamPluginActivator::~VslamPluginActivator()
{}

void VslamPluginActivator::start(ctkPluginContext* context)
{
	mRegistration = RegisteredService::create<VslamGUIExtenderService>(context, GUIExtenderService_iid);
}

void VslamPluginActivator::stop(ctkPluginContext* context)
{
	mRegistration.reset();
	Q_UNUSED(context);
}

} // namespace cx



