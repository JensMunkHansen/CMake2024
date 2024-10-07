import addpaths

from spsmodules.spsFiltersModeling import spsSimpleTriangleSubdivisionFilter
from spsmodules.util.scene_utils import (
    vtk_color_cells_randomly,
    vtk_color_points_randomly)

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2

from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkRenderingCore import (
    vtkRenderWindow,
    vtkActor,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkPolyDataMapper)

sphere = vtkSphereSource()
sphere.Update()
inPolyData = sphere.GetOutput()

vtk_color_points_randomly(inPolyData)

nInputPoints = inPolyData.GetNumberOfPoints()
nInputCells = inPolyData.GetNumberOfCells()

subdivision = spsSimpleTriangleSubdivisionFilter()
nSubDivisions = 1
subdivision.SetNumberOfSubdivisions(nSubDivisions)
subdivision.SetInputData(inPolyData)
subdivision.Update()

outPolyData = subdivision.GetOutput()

vtk_color_cells_randomly(outPolyData)

nOutputPoints = outPolyData.GetNumberOfPoints()
nOutputCells = outPolyData.GetNumberOfCells()
assert(nOutputPoints == nInputPoints + 0.5*(3**(nSubDivisions) - 1) * nInputCells)
assert(nOutputCells == nInputCells * 3**(nSubDivisions))

renderer = vtkRenderer()
mapper = vtkPolyDataMapper()
mapper.SetInputData(outPolyData)
mapper.SetScalarModeToUseCellData()

actor = vtkActor()
actor.SetMapper(mapper)

renderer.AddActor(actor)
rwin = vtkRenderWindow()
rwin.AddRenderer(renderer)
rwin.Render()
iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(rwin)
iren.Start()
