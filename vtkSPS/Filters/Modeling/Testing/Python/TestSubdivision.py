import addpaths

from spsmodules.spsFiltersModeling import spsSimpleTriangleSubdivisionFilter
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkCommonCore import (
  vtkUnsignedCharArray,
  vtkRandomPool)

sphere = vtkSphereSource()
sphere.Update()
inPolyData = sphere.GetOutput()

# TODO: Handle cell data interpolation
colors = vtkUnsignedCharArray()
colors.SetNumberOfComponents(3)
colors.SetNumberOfTuples(inPolyData.GetNumberOfPoints())
colors.SetName("Colors")

rnd = vtkRandomPool()
rnd.PopulateDataArray(colors, 0, 255)

inPolyData.GetPointData().SetScalars(colors)
inPolyData.GetPointData().SetActiveScalars("Colors")

nInputPoints = inPolyData.GetNumberOfPoints()
nInputCells = inPolyData.GetNumberOfCells()

subdivision = spsSimpleTriangleSubdivisionFilter()
#subdivision.DebugOn()
nSubDivisions = 1
subdivision.SetNumberOfSubdivisions(nSubDivisions)
subdivision.SetInputData(inPolyData)
subdivision.Update()

outPolyData = subdivision.GetOutput()
#outPolyData.GetPointData().SetActiveScalars("Colors")

cellColors = vtkUnsignedCharArray()
cellColors.SetNumberOfComponents(3)
cellColors.SetNumberOfTuples(outPolyData.GetNumberOfCells())
rnd.PopulateDataArray(cellColors, 0, 255)
outPolyData.GetCellData().SetScalars(cellColors)

nOutputPoints = outPolyData.GetNumberOfPoints()
nOutputCells = outPolyData.GetNumberOfCells()
assert(nOutputPoints == nInputPoints + 0.5*(3**(nSubDivisions) - 1) * nInputCells)
assert(nOutputCells == nInputCells * 3**(nSubDivisions))

import vtk
renderer = vtk.vtkRenderer()
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(outPolyData)
mapper.SetScalarModeToUseCellData()

actor = vtk.vtkActor()
actor.SetMapper(mapper)

renderer.AddActor(actor)
rwin = vtk.vtkRenderWindow()
rwin.AddRenderer(renderer)
rwin.Render()
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(rwin)
iren.Start()
