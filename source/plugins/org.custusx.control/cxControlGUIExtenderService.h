/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXCONTROLGUIEXTENDERSERVICE_H_
#define CXCONTROLGUIEXTENDERSERVICE_H_

#include "cxGUIExtenderService.h"
#include "org_custusx_control_Export.h"
class ctkPluginContext;

namespace cx
{

/**
 * Implementation of Control service.
 *
 * \ingroup org_custusx_control
 *
 * \date 2014-04-01
 * \author Christian Askeland
 */
class org_custusx_control_EXPORT ControlGUIExtenderService : public GUIExtenderService
{
	Q_INTERFACES(cx::GUIExtenderService)
public:
	ControlGUIExtenderService(ctkPluginContext *context);
	virtual ~ControlGUIExtenderService() {};

	std::vector<CategorizedWidget> createWidgets() const;

private:
  ctkPluginContext* mContext;

};
typedef boost::shared_ptr<ControlGUIExtenderService> ControlGUIExtenderServicePtr;

} /* namespace cx */

#endif /* CXCONTROLGUIEXTENDERSERVICE_H_ */

