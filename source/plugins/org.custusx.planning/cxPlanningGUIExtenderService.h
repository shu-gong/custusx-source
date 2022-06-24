/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.

Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.

CustusX is released under a BSD 3-Clause license.

See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXPLANNINGGUIEXTENDERSERVICE_H_
#define CXPLANNINGGUIEXTENDERSERVICE_H_

#include "cxGUIExtenderService.h"
#include "org_custusx_planning_Export.h"
class ctkPluginContext;

namespace cx
{

/**
 * Implementation of Planning service.
 *
 * \ingroup org_custusx_planning
 *
 * \date 2014-04-01
 * \author Christian Askeland
 */
class org_custusx_planning_EXPORT PlanningGUIExtenderService : public GUIExtenderService
{
    Q_INTERFACES(cx::GUIExtenderService)
public:
    PlanningGUIExtenderService(ctkPluginContext *context);
    virtual ~PlanningGUIExtenderService() {};

    std::vector<CategorizedWidget> createWidgets() const;

private:
  ctkPluginContext* mContext;

};
typedef boost::shared_ptr<PlanningGUIExtenderService> PlanningGUIExtenderServicePtr;

} /* namespace cx */

#endif /* CXPLANNINGGUIEXTENDERSERVICE_H_ */

