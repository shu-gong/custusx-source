/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxPlanningPluginActivator.h"

#include <QtPlugin>
#include <iostream>

#include "cxPlanningGUIExtenderService.h"
#include "cxRegisteredService.h"

namespace cx
{

PlanningPluginActivator::PlanningPluginActivator()
{
	std::cout << "Created PlanningPluginActivator" << std::endl;
}

PlanningPluginActivator::~PlanningPluginActivator()
{}

void PlanningPluginActivator::start(ctkPluginContext* context)
{
	mRegistration = RegisteredService::create<PlanningGUIExtenderService>(context, GUIExtenderService_iid);
}

void PlanningPluginActivator::stop(ctkPluginContext* context)
{
	mRegistration.reset();
	Q_UNUSED(context);
}

} // namespace cx



