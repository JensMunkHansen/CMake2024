#!/usr/bin/env python3

from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonCore import (
  vtkUnsignedCharArray,
  vtkRandomPool)
from vtkmodules.vtkCommonDataModel import vtkPolyData

def vtk_next_named_color(step=2):
  colors = vtkNamedColors()
  colorNames = colors.GetColorNames().split("\n")
  if not (vtk_next_named_color.iColor < len(colorNames)):
    vtk_next_named_color.iColor = 0
  colorName = colorNames[vtk_next_named_color.iColor]
  vtk_next_named_color.iColor = vtk_next_named_color.iColor + step
  return colors.GetColor3d(colorName)
vtk_next_named_color.iColor = 0

def vtk_color_all_cells(polyData:vtkPolyData, color = None):
    colors = vtkUnsignedCharArray()
    colors.SetNumberOfComponents(3)
    colors.SetNumberOfTuples(polyData.GetNumberOfCells())
    if color is None:
      color = vtk_next_named_color()
    colors.FillComponent(0, 255*color[0])
    colors.FillComponent(1, 255*color[1])
    colors.FillComponent(2, 255*color[2])
    polyData.GetCellData().SetScalars(colors)

def vtk_color_points_randomly(polyData:vtkPolyData):
  colors = vtkUnsignedCharArray()
  colors.SetNumberOfComponents(3)
  colors.SetNumberOfTuples(polyData.GetNumberOfPoints())
  colors.SetName("Colors")
  rnd = vtkRandomPool()
  rnd.PopulateDataArray(colors, 0, 255)
  polyData.GetPointData().SetScalars(colors)
  polyData.GetPointData().SetActiveScalars("Colors")

def vtk_color_cells_randomly(polyData:vtkPolyData):
  cellColors = vtkUnsignedCharArray()
  cellColors.SetNumberOfComponents(3)
  cellColors.SetNumberOfTuples(polyData.GetNumberOfCells())
  cellColors.SetName("Colors")

  rnd = vtkRandomPool()
  rnd.PopulateDataArray(cellColors, 0, 255)

  polyData.GetCellData().SetScalars(cellColors)
    

# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
