/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxControlGUIExtenderService.h"
#include "ctkPluginContext.h"
#include "cxControlWidget.h"

namespace cx
{

ControlGUIExtenderService::ControlGUIExtenderService(ctkPluginContext *context) :
  mContext(context)
{
}

std::vector<GUIExtenderService::CategorizedWidget> ControlGUIExtenderService::createWidgets() const
{
	std::vector<CategorizedWidget> retval;

	retval.push_back(GUIExtenderService::CategorizedWidget(
			new ControlWidget(),
			"Utility"));

	return retval;
}


} /* namespace cx */
