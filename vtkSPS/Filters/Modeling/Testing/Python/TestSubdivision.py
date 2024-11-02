import addpaths

from spsmodules.spsFiltersModeling import spsSimpleTriangleSubdivisionFilter
from spsmodules.util.scene_utils import (
    vtk_color_cells_randomly,
    vtk_color_points_randomly,
    vtk_subfigs)

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

rwin, renderers = vtk_subfigs(nrows=1, ncols=2, sharecamera=True)

mappers = []
mappers.append(vtkPolyDataMapper())
mappers[0].SetInputData(outPolyData)
mappers[0].SetScalarModeToUseCellData()

actors = []
actors.append(vtkActor())
actors[0].SetMapper(mappers[0])

renderers[0].AddActor(actors[0])

mappers.append(vtkPolyDataMapper())
mappers[1].SetInputData(inPolyData)
mappers[1].SetScalarModeToUseCellData()

actors.append(vtkActor())
actors[1].SetMapper(mappers[1])
renderers[1].AddActor(actors[1])

rwin.Render()
iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(rwin)
iren.Start()
