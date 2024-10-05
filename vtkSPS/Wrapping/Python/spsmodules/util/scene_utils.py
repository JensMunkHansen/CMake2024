#!/usr/bin/env python3

from vtkmodules.vtkCommonCore import vtkUnsignedCharArray
from vtkmodules.vtkCommonDataModel import vtkPolyData

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


# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
