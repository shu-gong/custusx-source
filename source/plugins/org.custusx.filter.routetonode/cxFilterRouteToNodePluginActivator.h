/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef CXFILTERROUTETONODEPLUGINACTIVATOR_H_
#define CXFILTERROUTETONODEPLUGINACTIVATOR_H_

#include <ctkPluginActivator.h>
#include "boost/shared_ptr.hpp"

namespace cx
{

typedef boost::shared_ptr<class RegisteredService> RegisteredServicePtr;

/**
 * Activator for the PNN reconstruction plugin
 *
 * \ingroup org_custusx_pnnreconstruction
 *
 * \date 2014-06-12
 * \author Janne Beate Bakeng, SINTEF
 * \author Ole Vegard Solberg, SINTEF
 */
class FilterRouteToNodePluginActivator :  public QObject, public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "org_custusx_filter_routetonode")

public:

  FilterRouteToNodePluginActivator();
  ~FilterRouteToNodePluginActivator();

  void start(ctkPluginContext* context);
  void stop(ctkPluginContext* context);

private:
	RegisteredServicePtr mRegistration;
};

} // namespace cx

#endif /* CXFILTERROUTETONODEPLUGINACTIVATOR_H_ */
