/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxNodeGUIExtenderService.h"
#include "ctkPluginContext.h"
#include "cxNodeWidget.h"

namespace cx
{

NodeGUIExtenderService::NodeGUIExtenderService(ctkPluginContext *context) :
  mContext(context)
{
}

std::vector<GUIExtenderService::CategorizedWidget> NodeGUIExtenderService::createWidgets() const
{
	std::vector<CategorizedWidget> retval;

	retval.push_back(GUIExtenderService::CategorizedWidget(
                        new NodeWidget(),
			"Utility"));

	return retval;
}


} /* namespace cx */
