/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#include "cxRouteToNodeFilterService.h"

#include <ctkPluginContext.h>
#include <QDir>

#include "cxAlgorithmHelpers.h"
#include "cxSelectDataStringProperty.h"

#include "cxUtilHelpers.h"
#include "cxRegistrationTransform.h"
#include "cxStringProperty.h"
#include "cxDoubleProperty.h"
#include "cxBoolProperty.h"
#include "cxTypeConversions.h"
#include "cxImage.h"

#include "cxRouteToNode.h"
#include "cxPatientModelService.h"
#include "cxPointMetric.h"
#include "cxVisServices.h"
#include "cxStringPropertySelectPointMetric.h"
#include "cxPatientModelServiceProxy.h"
#include "cxViewService.h"
#include "cxLog.h"

#include <vtkPolyData.h>


namespace cx
{

RouteToNodeFilter::RouteToNodeFilter(VisServicesPtr services, bool createRouteInformationFile) :
    FilterImpl(services),
    mGenerateFileWithRouteInformation(createRouteInformationFile),
    mSmoothing(true)
{
}

QString RouteToNodeFilter::getName() const
{
        return "Route to node";
}

QString RouteToNodeFilter::getType() const
{
        return "routetonode_filter";
}

QString RouteToNodeFilter::getHelp() const
{
	return "<html>"
                        "<h3>Route to node.</h3>"
                        "<p>Calculates the route to a selected node in navigated bronchocopy. "
			"The route starts at the top of trachea and ends at the most adjacent airway centerline"
                        "from the node.</p>"
           "</html>";
}

QString RouteToNodeFilter::getNameSuffix()
{
    return "_rtt_cl";
}

QString RouteToNodeFilter::getNameSuffixExtension()
{
    return "_ext";
}

QString RouteToNodeFilter::getNameSuffixBloodVessel()
{
    return "_vessel";
}

QString RouteToNodeFilter::getNameSuffixAirwayModel()
{
    return "_AirwaysModel";
}

QString RouteToNodeFilter::getNameSuffixAirwayAndVesselRTT()
{
    return "_AirwaysAndVessel_RTT";
}


void RouteToNodeFilter::createOptions()
{
	mOptionsAdapters.push_back(this->getBloodVesselOption(mOptions));
}

void RouteToNodeFilter::createInputTypes()
{
	StringPropertySelectMeshPtr centerline;
	centerline = StringPropertySelectMesh::New(mServices->patient());
	centerline->setValueName("Airways centerline");
	centerline->setHelp("Select airways centerline");
	mInputTypes.push_back(centerline);

        StringPropertySelectPointMetricPtr nodePoint;
        nodePoint = StringPropertySelectPointMetric::New(mServices->patient());
        nodePoint->setValueName("Node point");
        nodePoint->setHelp("Select node point metric");
        mInputTypes.push_back(nodePoint);

	StringPropertySelectMeshPtr bloodVesselCenterline;
	bloodVesselCenterline = StringPropertySelectMesh::New(mServices->patient());
	bloodVesselCenterline->setValueName("Blood vessel centerline");
	bloodVesselCenterline->setHelp("Select blood vessel centerline");
	mInputTypes.push_back(bloodVesselCenterline);

	SelectDataStringPropertyBasePtr bloodVesselSegmentationVolume;
	bloodVesselSegmentationVolume = StringPropertySelectImage::New(mServices->patient());
	bloodVesselSegmentationVolume->setValueName("Blood vessel segmentation volume");
	bloodVesselSegmentationVolume->setHelp("Select blood vessel segmentation volume");
	mInputTypes.push_back(bloodVesselSegmentationVolume);

}


void RouteToNodeFilter::createOutputTypes()
{
	StringPropertySelectMeshPtr tempRTTMeshStringAdapter;
	tempRTTMeshStringAdapter = StringPropertySelectMesh::New(mServices->patient());
        tempRTTMeshStringAdapter->setValueName("Route to node (mesh)");
        tempRTTMeshStringAdapter->setHelp("Generated route to node mesh (vtk-format).");
	mOutputTypes.push_back(tempRTTMeshStringAdapter);

	StringPropertySelectMeshPtr tempRTTEXTMeshStringAdapter;
	tempRTTEXTMeshStringAdapter = StringPropertySelectMesh::New(mServices->patient());
        tempRTTEXTMeshStringAdapter->setValueName("Route to node extended (mesh)");
        tempRTTEXTMeshStringAdapter->setHelp("Generated route to node extended mesh (vtk-format).");
	mOutputTypes.push_back(tempRTTEXTMeshStringAdapter);

	StringPropertySelectMeshPtr tempRTTVesselMeshStringAdapter;
	tempRTTVesselMeshStringAdapter = StringPropertySelectMesh::New(mServices->patient());
        tempRTTVesselMeshStringAdapter->setValueName("Route to node along blood vessels (mesh)");
        tempRTTVesselMeshStringAdapter->setHelp("Generated route to node along blood vessels mesh (vtk-format).");
	mOutputTypes.push_back(tempRTTVesselMeshStringAdapter);

	StringPropertySelectMeshPtr tempRTTVesselAndAirwayRTTMeshStringAdapter;
	tempRTTVesselAndAirwayRTTMeshStringAdapter = StringPropertySelectMesh::New(mServices->patient());
	tempRTTVesselAndAirwayRTTMeshStringAdapter->setValueName("Connected route - airways and vessels (mesh)");
        tempRTTVesselAndAirwayRTTMeshStringAdapter->setHelp("Connected route to node - airways and blood vessels mesh (vtk-format).");
	mOutputTypes.push_back(tempRTTVesselAndAirwayRTTMeshStringAdapter);

    StringPropertySelectMeshPtr tempAirwaysModelMeshStringAdapter;
    tempAirwaysModelMeshStringAdapter = StringPropertySelectMesh::New(mServices->patient());
    tempAirwaysModelMeshStringAdapter->setValueName("Airways along blood vessels surface model (mesh)");
    tempAirwaysModelMeshStringAdapter->setHelp("Generated airways surface model mesh (vtk-format).");
    mOutputTypes.push_back(tempAirwaysModelMeshStringAdapter);
}


bool RouteToNodeFilter::execute()
{
        mRouteToNode.reset(new RouteToNode());

	MeshPtr mesh = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[0])->getMesh();
	if (!mesh)
		return false;

        PointMetricPtr nodePoint = boost::dynamic_pointer_cast<StringPropertySelectPointMetric>(mInputTypes[1])->getPointMetric();
        if (!nodePoint)
		return false;

    mRouteToNode->setSmoothing(mSmoothing);

    mRouteToNode->processCenterline(mesh);

    //note: mOutput is in reference space
        mOutput = mRouteToNode->findRouteToNode(nodePoint);

	if(mOutput->GetNumberOfPoints() < 1)
		return false;

        mExtendedRoute = mRouteToNode->findExtendedRoute(nodePoint);

	if (mGenerateFileWithRouteInformation)
                mRouteToNode->addRouteInformationToFile(mServices);

	if (getBloodVesselOption(mOptions)->getValue())
	{
		ImagePtr bloodVesselVolume = this->getCopiedInputImage(3);

		MeshPtr bloodVesselCenterline = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[2])->getMesh();
		if (bloodVesselCenterline)
		{
			if (bloodVesselVolume)
                                mRouteToNode->setBloodVesselVolume(bloodVesselVolume);

                        mBloodVesselRoute = mRouteToNode->findRouteToNodeAlongBloodVesselCenterlines( bloodVesselCenterline, nodePoint);
                        mAirwaysFromBloodVessel = mRouteToNode->generateAirwaysFromBloodVesselCenterlines();
		}

                mAirwayAndBloodVesselRoute = mRouteToNode->getConnectedAirwayAndBloodVesselRoute();
	}
	return true;
}

bool RouteToNodeFilter::postProcess()
{

	MeshPtr inputMesh = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[0])->getMesh();
	if (!inputMesh)
		return false;

        PointMetricPtr nodePoint = boost::dynamic_pointer_cast<StringPropertySelectPointMetric>(mInputTypes[1])->getPointMetric();
        if (!nodePoint)
		return false;

        QString uidOutputCenterline = inputMesh->getName() + "_" + nodePoint->getName() + RouteToNodeFilter::getNameSuffix();
        QString nameOutputCenterline = inputMesh->getName() + "_" + nodePoint->getName() + RouteToNodeFilter::getNameSuffix();

	MeshPtr outputCenterline = patientService()->createSpecificData<Mesh>(uidOutputCenterline, nameOutputCenterline);
	outputCenterline->setVtkPolyData(mOutput);
    outputCenterline->getProperties().mLineWidth->setValue(5); //Setting thicker line for RTT
    patientService()->insertData(outputCenterline, true);

        QString uidCenterlineExt = outputCenterline->getUid() + RouteToNodeFilter::getNameSuffixExtension();
        QString nameCenterlineExt = outputCenterline->getName() + RouteToNodeFilter::getNameSuffixExtension();
	MeshPtr outputCenterlineExt = patientService()->createSpecificData<Mesh>(uidCenterlineExt, nameCenterlineExt);
	outputCenterlineExt->setVtkPolyData(mExtendedRoute);
	outputCenterlineExt->setColor(QColor(0, 0, 255, 255));
    outputCenterlineExt->getProperties().mLineWidth->setValue(5); //Setting thicker line for RTT
    patientService()->insertData(outputCenterlineExt, true);

	//note: mOutput and outputCenterline is in reference(r) space


	//Meshes are expected to be in data(d) space
	outputCenterline->get_rMd_History()->setParentSpace(inputMesh->getUid());
    outputCenterlineExt->get_rMd_History()->setParentSpace(inputMesh->getUid());

	mServices->view()->autoShowData(outputCenterline);

	if(mOutputTypes.size() > 0)
		mOutputTypes[0]->setValue(outputCenterline->getUid());
	if(mOutputTypes.size() > 1)
		mOutputTypes[1]->setValue(outputCenterlineExt->getUid());

	MeshPtr bloodVesselCenterlineMesh = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[2])->getMesh();
	if(mBloodVesselRoute && bloodVesselCenterlineMesh && getBloodVesselOption(mOptions)->getValue())
		postProcessBloodVessels();

//	//Create Ceetron route-to-node file
//	QString CeetronPath = mServices->patient()->getActivePatientFolder() + "/Images/MarianaRTT/";
//	QDir CeetronDirectory(CeetronPath);
//	if (!CeetronDirectory.exists()) // Creating MarianaRTT folder if it does not exist
//		CeetronDirectory.mkpath(CeetronPath);
//	QString filePathCeetron = CeetronPath + outputCenterline->getUid() + ".txt";
//	mRouteToNode->makeMarianaCenterlineFile(filePathCeetron);

	return true;
}

bool RouteToNodeFilter::postProcessBloodVessels()
{
	MeshPtr inputMesh = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[0])->getMesh();
        PointMetricPtr nodePoint = boost::dynamic_pointer_cast<StringPropertySelectPointMetric>(mInputTypes[1])->getPointMetric();
        QString uidOutputCenterline = inputMesh->getName() + "_" + nodePoint->getName() + RouteToNodeFilter::getNameSuffix();
        QString nameOutputCenterline = inputMesh->getName() + "_" + nodePoint->getName() + RouteToNodeFilter::getNameSuffix();
	MeshPtr outputCenterline = patientService()->createSpecificData<Mesh>(uidOutputCenterline, nameOutputCenterline);

	MeshPtr bloodVesselCenterlineMesh = boost::dynamic_pointer_cast<StringPropertySelectMesh>(mInputTypes[2])->getMesh();

        QString uidCenterlineBV = outputCenterline->getUid() + RouteToNodeFilter::getNameSuffixBloodVessel();
        QString nameCenterlineBV = outputCenterline->getName() + RouteToNodeFilter::getNameSuffixBloodVessel();
	MeshPtr outputCenterlineBV = patientService()->createSpecificData<Mesh>(uidCenterlineBV, nameCenterlineBV);
	outputCenterlineBV->setVtkPolyData(mBloodVesselRoute);
	outputCenterlineBV->setColor(QColor(0, 255, 0, 255));
	patientService()->insertData(outputCenterlineBV);

	outputCenterlineBV->get_rMd_History()->setParentSpace(inputMesh->getUid());

	if(mOutputTypes.size() > 2)
		mOutputTypes[2]->setValue(outputCenterlineBV->getUid());

	if(mAirwaysFromBloodVessel)
	{
                QString uidSurfaceModel = uidCenterlineBV + RouteToNodeFilter::getNameSuffixAirwayModel();
                QString nameSurfaceModel = nameCenterlineBV + RouteToNodeFilter::getNameSuffixAirwayModel();

		MeshPtr outputMesh = patientService()->createSpecificData<Mesh>(uidSurfaceModel, nameSurfaceModel);
		outputMesh->setVtkPolyData(mAirwaysFromBloodVessel);
        outputMesh->setColor(QColor(192, 253, 246, 255));
		patientService()->insertData(outputMesh);

		//Meshes are expected to be in data(d) space
		outputMesh->get_rMd_History()->setParentSpace(inputMesh->getUid());

		if(mOutputTypes.size() > 4)
			mOutputTypes[4]->setValue(outputMesh->getUid());

	}

        QString uidMergedCenterline = outputCenterline->getUid() + RouteToNodeFilter::getNameSuffixAirwayAndVesselRTT();
        QString nameMergedCenterline = outputCenterline->getName() + RouteToNodeFilter::getNameSuffixAirwayAndVesselRTT();
	MeshPtr outputMergedCenterline = patientService()->createSpecificData<Mesh>(uidMergedCenterline, nameMergedCenterline);
	outputMergedCenterline->setVtkPolyData(mAirwayAndBloodVesselRoute);
	outputMergedCenterline->setColor(QColor(0, 255, 0, 255));
    outputMergedCenterline->getProperties().mLineWidth->setValue(5); //Setting thicker line for RTT
	patientService()->insertData(outputMergedCenterline);

	outputMergedCenterline->get_rMd_History()->setParentSpace(inputMesh->getUid());

	if(mOutputTypes.size() >3)
		mOutputTypes[3]->setValue(outputMergedCenterline->getUid());

	return true;

}

void RouteToNodeFilter::setSmoothing(bool smoothing)
{
    mSmoothing = smoothing; // default true
}

std::vector< Eigen::Vector3d > RouteToNodeFilter::getRoutePositions()
{
        return mRouteToNode->getRoutePositions();
}

std::vector< double > RouteToNodeFilter::getCameraRotation()
{
        return mRouteToNode->getCameraRotation();
}

BoolPropertyPtr RouteToNodeFilter::getBloodVesselOption(QDomElement root)
{
	BoolPropertyPtr retval =
			BoolProperty::initialize("Use blood vessels to find RTT beyond airways",
					"",
					"Selecting this option to use blood vessels to find RTT beyond airways",
					false, root);
	return retval;

}


} // namespace cx

