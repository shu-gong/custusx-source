/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.

Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.

CustusX is released under a BSD 3-Clause license.

See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxPlanningGUIExtenderService.h"
#include "ctkPluginContext.h"
#include "cxPlanningWidget.h"

namespace cx
{

PlanningGUIExtenderService::PlanningGUIExtenderService(ctkPluginContext *context) :
  mContext(context)
{
}

std::vector<GUIExtenderService::CategorizedWidget> PlanningGUIExtenderService::createWidgets() const
{
    std::vector<CategorizedWidget> retval;

    retval.push_back(GUIExtenderService::CategorizedWidget(
            new PlanningWidget(),
            "Utility"));

    return retval;
}


} /* namespace cx */
