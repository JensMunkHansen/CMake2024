import addpaths

from spsmodules.spsIOGeneral import spsPolyDataPieceFilter

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2

from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonDataModel import vtkPolyData
from vtkmodules.vtkCommonCore import vtkUnsignedCharArray
from vtkmodules.vtkCommonExecutionModel import vtkStreamingDemandDrivenPipeline
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkRenderingCore import (
    vtkRenderWindow,
    vtkActor,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkPolyDataMapper)
from vtkmodules.vtkFiltersParallel import vtkPieceRequestFilter

from vtk.util.numpy_support import vtk_to_numpy
from vtk.util.numpy_support import numpy_to_vtk

import numpy as np

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

sphereSource = vtkSphereSource();
sphereSource.SetThetaResolution(30);
sphereSource.SetPhiResolution(30);
sphereSource.Update();

pieceFilter = spsPolyDataPieceFilter();

#pieceFilter.SetInputData(sphereSource.GetOutput()) # We split into pieces
pieceFilter.SetInputConnection(sphereSource.GetOutputPort()) # Pass-through, splitting handled upstream

# Renderer and window setup
renderer = vtkRenderer()
renderWindow = vtkRenderWindow()
renderWindow.AddRenderer(renderer)
interactor = vtkRenderWindowInteractor()
interactor.SetRenderWindow(renderWindow)

pieceFilter.UpdateInformation()

# Set up the number of pieces (streaming)
nPieces = 16
outInfo = pieceFilter.GetExecutive().GetOutputInformation(0)
outInfo.Set(vtkStreamingDemandDrivenPipeline.UPDATE_NUMBER_OF_PIECES(), nPieces)

for iPiece in range(nPieces):
    outInfo.Set(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER(), iPiece)
    pieceFilter.Update()
    print("UPDATE_PIECE_NUMBER(spsPolyDataPieceFilter): %d" % (iPiece))
    iUpstreamPiece = sphereSource.GetOutputInformation(0).Get(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER())
    print("UPDATE_PIECE_NUMBER(vtkSphereSource): " + str(iUpstreamPiece))
    # Take a copy
    polyData = vtkPolyData()
    polyData.DeepCopy(pieceFilter.GetOutput())
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

