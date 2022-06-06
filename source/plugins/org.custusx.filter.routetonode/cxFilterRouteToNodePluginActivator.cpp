/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxFilterRouteToNodePluginActivator.h"

#include <QtPlugin>
#include <iostream>

#include "cxRouteToNodeFilterService.h"
#include "cxRegisteredService.h"
#include "cxVisServices.h"

namespace cx
{

FilterRouteToNodePluginActivator::FilterRouteToNodePluginActivator()
{
}

FilterRouteToNodePluginActivator::~FilterRouteToNodePluginActivator()
{
}

void FilterRouteToNodePluginActivator::start(ctkPluginContext* context)
{
	VisServicesPtr services = VisServices::create(context);
        RouteToNodeFilter *routeToNodeFilter = new RouteToNodeFilter(services);
        mRegistration = RegisteredService::create(context, routeToNodeFilter, FilterService_iid);
}

void FilterRouteToNodePluginActivator::stop(ctkPluginContext* context)
{
    mRegistration.reset();
	Q_UNUSED(context);
}

} // namespace cx



