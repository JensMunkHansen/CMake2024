import addpaths

from spsmodules.spsIOGeneral import spsPolyDataPieceFilter
from spsmodules.util.scene_utils import vtk_color_all_cells

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2

from vtkmodules.vtkCommonDataModel import vtkPolyData
from vtkmodules.vtkCommonCore import vtkUnsignedCharArray
from vtkmodules.vtkCommonExecutionModel import vtkStreamingDemandDrivenPipeline
from vtkmodules.vtkFiltersCore import vtkAppendPolyData
from vtkmodules.vtkFiltersGeometry import vtkGeometryFilter
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkRenderingCore import (
    vtkRenderWindow,
    vtkActor,
    vtkRenderWindowInteractor,
    vtkRenderer,
    vtkDataSetMapper,
    vtkPolyDataMapper)
from vtkmodules.vtkFiltersParallel import vtkPieceRequestFilter

import numpy as np
import vtk

sphereSource = vtkSphereSource();
sphereSource.SetThetaResolution(30);
sphereSource.SetPhiResolution(30);
sphereSource.Update();

pieceFilter = spsPolyDataPieceFilter();

pieceFilter.SetInputData(sphereSource.GetOutput()) # We split into pieces
#pieceFilter.SetInputConnection(sphereSource.GetOutputPort()) # We split into pieces

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

append = vtkAppendPolyData()
append.SetInputConnection(pieceFilter.GetOutputPort())
for iPiece in range(nPieces):
    outInfo.Set(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER(), iPiece)
    pieceFilter.Update()
    print("UPDATE_PIECE_NUMBER(spsPolyDataPieceFilter): %d" % (iPiece))
    iUpstreamPiece = sphereSource.GetOutputInformation(0).Get(vtkStreamingDemandDrivenPipeline.UPDATE_PIECE_NUMBER())
    print("UPDATE_PIECE_NUMBER(vtkSphereSource): " + str(iUpstreamPiece))
    # Take a copy
    polyData = vtkPolyData()
    polyData.DeepCopy(pieceFilter.GetOutput())
    #append.AddInputData(polyData)
    append.Update()
    # Debug
    print("#cells: " + str(polyData.GetNumberOfCells()))
    print("#points: " + str(polyData.GetNumberOfPoints()))
    # Color the mesh
    vtk_color_all_cells(polyData)
    # Display
    mapper = vtkPolyDataMapper()
    mapper.SetInputData(polyData)
    mapper.SetScalarModeToUseCellData()
    actor = vtkActor()
    actor.SetMapper(mapper)
    #renderer.AddActor(actor)
actor = vtkActor()


# Could use append filter and geometry filter (no deepcopy). Leave only outer shell as poly data
mapper = vtkDataSetMapper()
mapper.SetInputData(append.GetOutput())
actor.SetMapper(mapper)
renderer.AddActor(actor)

# Start rendering
renderWindow.Render()
interactor.Start()

