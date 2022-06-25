/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.

Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.

CustusX is released under a BSD 3-Clause license.

See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXVSLAMGUIEXTENDERSERVICE_H_
#define CXVSLAMGUIEXTENDERSERVICE_H_

#include "cxGUIExtenderService.h"
#include "org_custusx_vslam_Export.h"
class ctkPluginContext;

namespace cx
{

/**
 * Implementation of Vslam service.
 *
 * \ingroup org_custusx_vslam
 *
 * \date 2014-04-01
 * \author Christian Askeland
 */
class org_custusx_vslam_EXPORT VslamGUIExtenderService : public GUIExtenderService
{
    Q_INTERFACES(cx::GUIExtenderService)
public:
    VslamGUIExtenderService(ctkPluginContext *context);
    virtual ~VslamGUIExtenderService() {};

    std::vector<CategorizedWidget> createWidgets() const;

private:
  ctkPluginContext* mContext;

};
typedef boost::shared_ptr<VslamGUIExtenderService> VslamGUIExtenderServicePtr;

} /* namespace cx */

#endif /* CXVSLAMGUIEXTENDERSERVICE_H_ */

