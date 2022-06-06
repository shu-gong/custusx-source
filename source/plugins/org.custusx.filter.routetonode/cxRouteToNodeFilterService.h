/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/
#ifndef CXROUTETONODEFILTER_H
#define CXROUTETONODEFILTER_H

#include "org_custusx_filter_routetonode_Export.h"

#include "cxPatientModelService.h"
#include "cxFilterImpl.h"

class ctkPluginContext;

namespace cx
{

/** Filter to calculates the route to a selected node in navigated bronchocopy.
 * The rout starts at the top of trachea and ends at the most adjacent airway centerline
 *  from the node.</p>
 * \ingroup cx_module_algorithm
 * \date Jan 29, 2015
 * \author Erlend Fagertun Hofstad
 */


typedef boost::shared_ptr<class RouteToNode> RouteToNodePtr;
typedef boost::shared_ptr<class BranchList> BranchListPtr;

class org_custusx_filter_routetonode_EXPORT RouteToNodeFilter : public FilterImpl
{
	Q_OBJECT
	Q_INTERFACES(cx::Filter)

public:
        RouteToNodeFilter(VisServicesPtr services, bool createRouteInformationFile = false);
        virtual ~RouteToNodeFilter() {}

	virtual QString getType() const;
	virtual QString getName() const;
	virtual QString getHelp() const;
	static QString getNameSuffix();
	static QString getNameSuffixExtension();
	static QString getNameSuffixBloodVessel();
	static QString getNameSuffixAirwayModel();
	static QString getNameSuffixAirwayAndVesselRTT();

	std::vector< Eigen::Vector3d > getRoutePositions();
	std::vector< double > getCameraRotation();

	virtual bool execute();
	virtual bool postProcess();
	virtual bool postProcessBloodVessels();
    void setSmoothing(bool smoothing = true);

protected:
	virtual void createOptions();
	virtual void createInputTypes();
	virtual void createOutputTypes();

private slots:

private:
        RouteToNodePtr mRouteToNode;
	vtkPolyDataPtr mOutput;
    vtkPolyDataPtr mExtendedRoute;
    vtkPolyDataPtr 	mBloodVesselRoute;
    vtkPolyDataPtr mAirwaysFromBloodVessel;
    vtkPolyDataPtr mAirwayAndBloodVesselRoute;
    BranchListPtr mBranchListPtr;
    bool mGenerateFileWithRouteInformation;
    bool mSmoothing;
    BoolPropertyPtr getBloodVesselOption(QDomElement root);
};
typedef boost::shared_ptr<class RouteToNodeFilter> RouteToNodeFilterPtr;


} // namespace cx



#endif // CXROUTETONODEFILTER_H
