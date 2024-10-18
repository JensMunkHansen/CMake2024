#!/usr/bin/env python

import sys
import os

from SpsDisplacementFilterSolution import SpsDisplacementPolyDataFilter

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkCommonColor import vtkNamedColors

from vtkmodules.vtkCommonDataModel import (
  vtkPlane,
)
from vtkmodules.vtkFiltersCore import (
  vtkPolyDataNormals,
  vtkCleanPolyData,
  vtkClipPolyData,
  vtkDecimatePro,
)
from vtkmodules.vtkFiltersGeneral import (
  vtkTransformPolyDataFilter
)

from vtkmodules.vtkFiltersSources import (
  vtkSphereSource,
  vtkArrowSource
)
from vtkmodules.vtkCommonTransforms import (
  vtkTransform
)
from vtkmodules.vtkRenderingAnnotation import (
  vtkScalarBarActor,
)
from vtkmodules.vtkRenderingCore import (
  vtkActor,
  vtkPolyDataMapper,
  vtkGlyph3DMapper,
  vtkRenderWindow,
  vtkRenderWindowInteractor,
  vtkRenderer
)

def create_clipped_sphere_source(offset, radius=10):
  sphere = vtkSphereSource()
  sphere.SetCenter(0, 0, 0)
  sphere.SetPhiResolution(8)
  sphere.SetThetaResolution(16)
  sphere.SetRadius(radius)
  
  plane = vtkPlane()
  plane.SetOrigin(0, 0, 5)
  plane.SetNormal(0, 0, 1)

  clipper = vtkClipPolyData()
  clipper.SetInputConnection(sphere.GetOutputPort())
  clipper.SetClipFunction(plane)
  clipper.SetValue(0)
  clipper.Update()
  
  transform = vtkTransform()
  transform.Translate(offset[0], offset[1], offset[2])
  transformFilter = vtkTransformPolyDataFilter()
  transformFilter.SetTransform(transform)
  transformFilter.SetInputConnection(clipper.GetOutputPort())
  transformFilter.Update()
  return transformFilter

def main(argv):
  input1 = None
  input2 = None
  if (len(argv) == 3):
    reader1 = vtkPLYReader()
    reader1.SetFileName(argv[1])
    reader1.Update()
    input1 = reader1.GetOutput()
      
    reader2 = vtkPLYReader()
    reader2.SetFileName(argv[2])
    reader2.Update()
    input2 = reader2.GetOutput()
  else:
    # Arrow on this object
    sphereSource1 = create_clipped_sphere_source((6,0,0), 20)
    sphereSource1.Update()  
    input1 = sphereSource1.GetOutput()
    
    sphereSource2 = create_clipped_sphere_source((0,0,2), 20)
    sphereSource2.Update()  
    input2 = sphereSource2.GetOutput()  
      
  colors = vtkNamedColors()
  
  clean1 = vtkCleanPolyData()
  clean1.SetInputData(input1)
  clean1.Update()
  
  clean2 = vtkCleanPolyData()
  clean2.SetInputData(input2)
  
  # Subsampling
  decimate = vtkDecimatePro()
  decimate.SetInputConnection(clean1.GetOutputPort())
  decimate.SetTargetReduction(0.9) # Result is 10%
  decimate.PreserveTopologyOn()
  decimate.Update()
  
  displacementFilter = SpsDisplacementPolyDataFilter()
  displacementFilter.SetInputConnection(0, decimate.GetOutputPort())
  displacementFilter.SetInputConnection(1, clean2.GetOutputPort())
  displacementFilter.SignedDistanceOn()
  displacementFilter.NegateDistanceOn()
  displacementFilter.GradientOn()
  displacementFilter.ComputeCellCenterDisplacementOn()
  displacementFilter.Update()
  
  scalars = displacementFilter.GetOutput().GetPointData().GetScalars()
  rng = [scalars.GetRange()[0],
         scalars.GetRange()[1]]
  lim = max([abs(v) for v in rng])
  
  arrow_source = vtkArrowSource()
  
  displacementMapper = vtkGlyph3DMapper()
  displacementMapper.SetInputConnection(displacementFilter.GetOutputPort())
  displacementMapper.SetSourceConnection(arrow_source.GetOutputPort())
  displacementMapper.SetScaleArray("Distance")
  displacementMapper.SetScalarRange(-lim, lim)
  displacementMapper.ScalingOn()
  displacementMapper.SetScaleMode(displacementMapper.SCALE_BY_MAGNITUDE)
  displacementMapper.SetColorModeToMapScalars()
  displacementActor = vtkActor()
  displacementActor.SetMapper(displacementMapper)
  displacementActor.GetProperty().SetColor(colors.GetColor3d("Red"))
  
  sphereMapper2 = vtkPolyDataMapper()
  sphereMapper2.SetInputConnection(clean2.GetOutputPort())
  sphereActor2 = vtkActor()
  sphereActor2.SetMapper(sphereMapper2)
  sphereActor2.GetProperty().SetColor(colors.GetColor3d("Green"))
  sphereActor2.GetProperty().SetRepresentationToWireframe()
  
  sphereMapper1 = vtkPolyDataMapper()
  #sphereMapper1.SetInputConnection(displacementFilter.GetOutputPort(0))
  sphereMapper1.SetInputConnection(clean1.GetOutputPort())
  
  sphereActor1 = vtkActor()
  sphereActor1.SetMapper(sphereMapper1)
  
  
  scalarBar = vtkScalarBarActor()
  scalarBar.SetLookupTable(displacementMapper.GetLookupTable())
  scalarBar.SetTitle("Distance")
  scalarBar.SetNumberOfLabels(4)
  scalarBar.UnconstrainedFontSizeOn()
  
  renderer = vtkRenderer()
  renderer.SetBackground(colors.GetColor3d("Silver"))
  renderer.SetBackground2(colors.GetColor3d("Gold"))
  renderer.GradientBackgroundOn()
  
  renWin = vtkRenderWindow()
  renWin.AddRenderer(renderer)
  renWin.SetSize(600, 500)
  renWin.SetWindowName("DistancePolyDataFilter")
  
  renWinInteractor = vtkRenderWindowInteractor()
  renWinInteractor.SetRenderWindow(renWin)
  
  renderer.AddActor(displacementActor)
  renderer.AddActor(sphereActor1)
  renderer.AddActor(sphereActor2)
  renderer.AddActor(scalarBar)
  
  renWin.Render()
  renWinInteractor.Start()

if __name__ == "__main__":
  main(sys.argv)


# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
