#!/usr/bin/env python
"""Test style for painting on a mesh."""

# Try to use vtkClipPolyData to introduce new edges
# Use quadric clustering to reduce the mesh

from InteractorStyleMesh import InteractorStyleMesh

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle

# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2  # noqa
from vtkmodules.vtkCommonCore import vtkSMPTools
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkFiltersSources import vtkSphereSource

from vtkmodules.vtkRenderingCore import (
  vtkActor,
  vtkPolyDataMapper,
  vtkRenderWindow,
  vtkRenderWindowInteractor,
  vtkRenderer
)

from vtkmodules.vtkFiltersCore import vtkGenerateIds
from vtkmodules.vtkFiltersGeneral import vtkTransformPolyDataFilter
from vtkmodules.vtkFiltersGeometry import vtkDataSetSurfaceFilter
from vtkmodules.vtkCommonTransforms import vtkTransform

from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera

def main():
  smp = vtkSMPTools()
  smp.SetBackend("TBB")
  """Enter here."""
  source = vtkSphereSource()
  source.SetPhiResolution(84)
  source.SetThetaResolution(160)
  source.SetStartPhi(90)
  source.SetRadius(20)
  source.Update()
  polyData0 = source.GetOutput()

  transformFilter = vtkTransformPolyDataFilter()
  transform = vtkTransform()
  transform.RotateX(90)
  transform.Modified()

  transformFilter.SetTransform(transform)
  transformFilter.SetInputData(polyData0)
  transformFilter.Update()

  polyData = transformFilter.GetOutput()

  colors = vtkNamedColors()

  # Why?
  idFilter = vtkGenerateIds()
  idFilter.SetInputData(polyData)
  idFilter.SetCellIdsArrayName("OriginalIds")
  idFilter.SetPointIdsArrayName("OriginalIds")
  idFilter.Update()

  # This is needed to convert the ouput of vtkIdFilter (vtkDataSet) back to
  # vtkPolyData
  surfaceFilter = vtkDataSetSurfaceFilter()
  surfaceFilter.SetInputData(polyData)
  surfaceFilter.Update()

  inputData = surfaceFilter.GetOutput()

  # Create a mapper and actor
  mapper = vtkPolyDataMapper()
  mapper.SetInputData(polyData)
  mapper.ScalarVisibilityOff()

  actor = vtkActor()
  actor.SetMapper(mapper)
  actor.GetProperty().SetPointSize(5)
  actor.GetProperty().SetDiffuseColor(colors.GetColor3d("Peacock"))
  # Visualize
  renderer = vtkRenderer()
  renderer.UseHiddenLineRemovalOn()

  renderWindow = vtkRenderWindow()
  renderWindow.AddRenderer(renderer)
  renderWindow.SetSize(640, 480)
  renderWindow.SetWindowName("HighlightSelection")

  renderWindowInteractor = vtkRenderWindowInteractor()
  renderWindowInteractor.SetRenderWindow(renderWindow)

  renderer.AddActor(actor)
  renderer.SetBackground(colors.GetColor3d("Tan"))

  renderWindow.Render()

  style = InteractorStyleMesh(None, renderWindowInteractor, renderer)
  # Can be done by just setting actor
  style.SetActor(actor)
  renderWindowInteractor.SetInteractorStyle(style)

  def switch(obj, ev):
    if obj.GetKeySym() == 't':
      if switch.Enabled:
        track = vtkInteractorStyleTrackballCamera()
        obj.SetInteractorStyle(track)
      else:
        obj.SetInteractorStyle(style)
      switch.Enabled = not switch.Enabled
  renderWindowInteractor.AddObserver('KeyPressEvent', switch)
  switch.Enabled = True
  
  renderWindowInteractor.Start()


if __name__ == "__main__":
  main()
