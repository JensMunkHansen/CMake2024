import addpaths

from spsmodules.spsFiltersModeling import spsSimpleTriangleSubdivisionFilter
from spsmodules.spsIOGeneral import spsPolyDataPieceFilter

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonCore import (
    vtkUnsignedCharArray,
    vtkRandomPool)
from vtkmodules.vtkCommonDataModel import vtkPolyData
from vtkmodules.vtkCommonExecutionModel import vtkStreamingDemandDrivenPipeline
from vtkmodules.vtkRenderingCore import (
    vtkRenderWindow,
    vtkActor,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkPolyDataMapper)

namedColors = vtkNamedColors()

def colorMesh(polyData:vtkPolyData, iPiece):
    colors = vtkUnsignedCharArray()
    colors.SetNumberOfComponents(3)
    colors.SetNumberOfTuples(polyData.GetNumberOfCells())
    colorName = namedColors.GetColorNames().split('\n')[iPiece]
    rgb = [0.0, 0.0, 0.0]
    namedColors.GetColorRGB(colorName, rgb)
    colors.FillComponent(0, 255*rgb[0])
    colors.FillComponent(1, 255*rgb[1])
    colors.FillComponent(2, 255*rgb[2])
    polyData.GetCellData().SetScalars(colors)

sphereSource = vtkSphereSource()
sphereSource.Update()
inPolyData = sphereSource.GetOutput()

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

pieceFilter = spsPolyDataPieceFilter()
pieceFilter.SetInputData(inPolyData)

subdivision = spsSimpleTriangleSubdivisionFilter()
#subdivision.DebugOn()
nSubDivisions = 1
subdivision.SetNumberOfSubdivisions(nSubDivisions)
#subdivision.SetInputConnection(sphereSource.GetOutputPort())
subdivision.SetInputConnection(pieceFilter.GetOutputPort())

# Renderer and window setup
renderer = vtkRenderer()
renderWindow = vtkRenderWindow()
renderWindow.AddRenderer(renderer)
interactor = vtkRenderWindowInteractor()
interactor.SetRenderWindow(renderWindow)

subdivision.UpdateInformation()

nPieces = 4
outInfo = subdivision.GetExecutive().GetOutputInformation(0)
outInfo.Set(vtkStreamingDemandDrivenPipeline.UPDATE_NUMBER_OF_PIECES(), nPieces)

for iPiece in range(nPieces):
    outInfo.Set(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER(), iPiece)
    subdivision.Update()
    print("UPDATE_PIECE_NUMBER(spsPolyDataPieceFilter): %d" % (iPiece))
    iUpstreamPiece = sphereSource.GetOutputInformation(0).Get(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER())
    print("UPDATE_PIECE_NUMBER(vtkSphereSource): " + str(iUpstreamPiece))
    # Take a copy
    polyData = vtkPolyData()
    polyData.DeepCopy(subdivision.GetOutput())
    # Debug
    print("#cells: " + str(polyData.GetNumberOfCells()))
    print("#points: " + str(polyData.GetNumberOfPoints()))
    # Color the mesh
    colorMesh(polyData, iPiece)
    # Display
    mapper = vtkPolyDataMapper()
    mapper.SetInputData(polyData)
    mapper.SetScalarModeToUseCellData()
    actor = vtkActor()
    actor.SetMapper(mapper)
    renderer.AddActor(actor)

# Start rendering
renderWindow.Render()
interactor.Start()
