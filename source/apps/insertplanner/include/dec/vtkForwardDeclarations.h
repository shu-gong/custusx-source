/*=========================================================================
This file is part of CustusX, an Image Guided Therapy Application.
                 
Copyright (c) SINTEF Department of Medical Technology.
All rights reserved.
                 
CustusX is released under a BSD 3-Clause license.
                 
See Lisence.txt (https://github.com/SINTEFMedtek/CustusX/blob/master/License.txt) for details.
=========================================================================*/

#ifndef VTKFORWARDDECLARATIONS_H_
#define VTKFORWARDDECLARATIONS_H_

#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

/**
 * \brief File for vtk forwarddeclarations
 *
 * \date 26. okt. 2010
 * \author: Janne Beate Bakeng, SINTEF
 */

// KEEP SORTED AND UNIQUE!


typedef vtkSmartPointer<class vtkCellArray> vtkCellArrayPtr;
typedef vtkSmartPointer<class vtkPoints> vtkPointsPtr;
typedef vtkSmartPointer<class vtkPolyData> vtkPolyDataPtr;


class vtkObject;
class vtkOpenGLExtensionManager;
class vtkRenderWindowInteractor;
class vtkTextProperty;
class vtkViewport;


#endif /* VTKFORWARDDECLARATIONS_H_ */

