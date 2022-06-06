/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXNODEGUIEXTENDERSERVICE_H_
#define CXNODEGUIEXTENDERSERVICE_H_

#include "cxGUIExtenderService.h"
#include "org_custusx_node_Export.h"
class ctkPluginContext;

namespace cx
{

/**
 * Implementation of Example service.
 *
 * \ingroup org_custusx_example
 *
 * \date 2014-04-01
 * \author Christian Askeland
 */
class org_custusx_node_EXPORT NodeGUIExtenderService : public GUIExtenderService
{
	Q_INTERFACES(cx::GUIExtenderService)
public:
	NodeGUIExtenderService(ctkPluginContext *context);
	virtual ~NodeGUIExtenderService() {};

	std::vector<CategorizedWidget> createWidgets() const;

private:
  ctkPluginContext* mContext;

};
typedef boost::shared_ptr<NodeGUIExtenderService> NodeGUIExtenderServicePtr;

} /* namespace cx */

#endif /* CXNODEGUIEXTENDERSERVICE_H_ */

