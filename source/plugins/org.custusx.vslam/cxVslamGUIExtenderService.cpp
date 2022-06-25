/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.

Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.

CustusX is released under a BSD 3-Clause license.

See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxVslamGUIExtenderService.h"
#include "ctkPluginContext.h"
#include "cxVslamWidget.h"

namespace cx
{

VslamGUIExtenderService::VslamGUIExtenderService(ctkPluginContext *context) :
  mContext(context)
{
}

std::vector<GUIExtenderService::CategorizedWidget> VslamGUIExtenderService::createWidgets() const
{
    std::vector<CategorizedWidget> retval;

    retval.push_back(GUIExtenderService::CategorizedWidget(
            new VslamWidget(),
            "Utility"));

    return retval;
}


} /* namespace cx */
