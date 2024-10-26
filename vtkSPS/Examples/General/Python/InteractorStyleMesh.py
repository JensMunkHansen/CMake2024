"""Style for painting on a mesh."""

import numpy as np
import vtkmodules.all as vtk
from vtkmodules.vtkCommonCore import vtkCommand, vtkUnsignedCharArray
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonDataModel import (
  vtkSphere,
  vtkPolyData
)
from vtkmodules.vtkFiltersExtraction import vtkExtractPolyDataGeometry
from vtkmodules.vtkFiltersCore import (
  vtkCleanPolyData,
  vtkClipPolyData,
  vtkDecimatePro,
  vtkQuadricClustering)

from vtkmodules.vtkInteractionWidgets import vtkPolygonalSurfacePointPlacer

from vtkmodules.vtkRenderingCore import (
  vtkActor,
  vtkPolyDataMapper,
  vtkDataSetMapper,
)
from vtkmodules.vtkFiltersCore import vtkAppendPolyData


class InteractorStyleMesh(vtk.vtkInteractorStyle):
  """
  Class semi copy/paste from InteractorStyleDrawPolygon
  """  # noqa: E501

  class vtkInternal(object):
    """Class internal to InteractorStyleDrawPolygon to help with drawing the polygon."""

    def __init__(self, parent=None):  # noqa: D107
        super().__init__()
        self._points = []

    @property
    def points(self):  # noqa: D102
      return np.array(self._points)

    def AddPoint(self, x, y):  # noqa: D102
      self._points.append([x, y])

    def GetPoint(self, index):  # noqa: D102
      if index < 0 or index > len(self._points) - 1:
        return
      return np.array(self._points[index])

    def GetNumberOfPoints(self):  # noqa: D102
      return len(self._points)

    def Clear(self):  # noqa: D102
      self._points = []

  def __init__(self, parent=None, interactor=None, renderer=None):  # noqa: D107
    self.parent = parent
    self.interactor = interactor
    self.renderer = renderer
    self.polyData = None
    self.actor = None
    self.placer = None
    self.selectedActor = vtkActor()
    self.selectedMapper = vtkDataSetMapper()
    self.alwaysOnTop = True
    vtkPolyDataMapper.SetResolveCoincidentTopologyToPolygonOffset()
    if (self.alwaysOnTop):
      self.selectedMapper.SetRelativeCoincidentTopologyLineOffsetParameters(0, -66000)
      self.selectedMapper.SetRelativeCoincidentTopologyPolygonOffsetParameters(0, -66000)
      self.selectedMapper.SetRelativeCoincidentTopologyPointOffsetParameter(-66000)
    else:
      self.selectedMapper.SetRelativeCoincidentTopologyLineOffsetParameters(-1, -1)
      self.selectedMapper.SetRelativeCoincidentTopologyPolygonOffsetParameters(-1, -1)
      self.selectedMapper.SetRelativeCoincidentTopologyPointOffsetParameter(-1)

    self.selectedActor.SetMapper(self.selectedMapper)

    self.AddObserver("MouseMoveEvent", self.OnMouseMove)
    self.AddObserver("LeftButtonPressEvent", self.OnLeftButtonDown)
    self.AddObserver("LeftButtonReleaseEvent", self.OnLeftButtonUp)
    self.AddObserver("RightButtonPressEvent", self.OnRightButtonDown)
    self.setup()

  def setup(self):
    """Set up the internals."""
    colors = vtkNamedColors()
    self.Internal = self.vtkInternal()
    self.StartPosition = np.zeros(2, dtype=np.int32)
    self.EndPosition = np.zeros(2, dtype=np.int32)
    self.Moving = False
    self.sphere = vtkSphere()
    self.sphere.SetRadius(4.0)
    self.mode = 1
    self.inputFilter = None
    self.outputFilter = None
    if self.mode == 0:
      extractPolyDataGeometry = vtkExtractPolyDataGeometry()
      extractPolyDataGeometry.SetImplicitFunction(self.sphere)
      self.inputFilter = extractPolyDataGeometry
      self.outputFilter = extractPolyDataGeometry
    elif self.mode == 1:
      clipPolyData = vtkClipPolyData()
      clipPolyData.SetClipFunction(self.sphere)
      clipPolyData.SetGenerateClippedOutput(True)
      clipPolyData.InsideOutOn()
      self.inputFilter = clipPolyData
      self.outputFilter = clipPolyData
    elif self.mode == 2:
      clipPolyData = vtkClipPolyData()
      clipPolyData.SetClipFunction(self.sphere)
      clipPolyData.SetGenerateClippedOutput(True)
      clipPolyData.InsideOutOn()
      self.inputFilter = clipPolyData
      clustering = vtkQuadricClustering()
      clustering.SetNumberOfXDivisions(100)
      clustering.SetNumberOfYDivisions(100)
      clustering.SetNumberOfZDivisions(100)
      clustering.SetInputConnection(self.inputFilter.GetOutputPort())
      self.outputFilter = clustering
    else:
      clipPolyData = vtkClipPolyData()
      clipPolyData.SetClipFunction(self.sphere)
      clipPolyData.SetGenerateClippedOutput(True)
      clipPolyData.InsideOutOn()
      self.inputFilter = clipPolyData
      clustering = vtkQuadricClustering()
      clustering.SetNumberOfXDivisions(100)
      clustering.SetNumberOfYDivisions(100)
      clustering.SetNumberOfZDivisions(100)
      clustering.SetInputConnection(self.inputFilter.GetOutputPort())
      decimate = vtk.vtkDecimatePro()
      decimate.SetInputConnection(clustering.GetOutputPort())
      # Make this a variable (of the number appended)
      decimate.SetTargetReduction(0.5)  # Reduce the triangle count by 50%
      decimate.PreserveTopologyOn()     # Optional: maintain mesh topology
      self.outputFilter = decimate
    self.selectedMapper.ScalarVisibilityOff()
    self.selectedActor.GetProperty().SetColor(colors.GetColor3d("Tomato"))
    self.selectedActor.GetProperty().SetPointSize(5)
    self.selectedActor.GetProperty().SetRepresentationToWireframe()
    self.lastCellId = -1
    self.appendPolyData = vtkAppendPolyData()
    self.cleanPolyData = vtkCleanPolyData()
    self.cleanPolyData.SetInputConnection(self.appendPolyData.GetOutputPort())
    if False: #self.mode == 1:
      decimate = vtk.vtkDecimatePro()
      decimate.SetInputConnection(self.cleanPolyData.GetOutputPort())
      decimate.SetTargetReduction(0.9)  # Reduce the triangle count by 90%
      decimate.PreserveTopologyOn()     # Optional: maintain mesh topology
      mapperInput = decimate
    else:
      mapperInput = self.cleanPolyData
    self.selectedMapper.SetInputConnection(mapperInput.GetOutputPort())

  def SetActor(self, actor):  # noqa
    # TODO: Test presence
    self.actor = actor
    self.polyData = self.actor.GetMapper().GetInputDataObject(0,0)
    self.placer = vtkPolygonalSurfacePointPlacer()
    self.placer.AddProp(self.actor)
    self.placer.GetPolys().AddItem(self.polyData)
    self.inputFilter.SetInputData(self.polyData)
    self.Modified()

  def OnRightButtonDown(self, obj, event):  # noqa
    if self.renderer.HasViewProp(self.selectedActor):
      self.renderer.RemoveActor(self.selectedActor)
      self.appendPolyData.SetInputData(None)
      self.cleanPolyData.SetInputConnection(self.appendPolyData.GetOutputPort())
    self.renderer.GetRenderWindow().Render()

  def OnLeftButtonDown(self, obj, event):
    """Left mouse button press event."""
    if self.interactor is None:
      return

    self.Moving = True
    eventPos = self.interactor.GetEventPosition()
    self.StartPosition[0], self.StartPosition[1] = eventPos[0], eventPos[1]
    self.EndPosition = self.StartPosition

    self.Internal.Clear()
    self.Internal.AddPoint(self.StartPosition[0], self.StartPosition[1])

    if (self.polyData is not None):
        X, Y = self.interactor.GetEventPosition()
        displayPos = [float(X), float(Y)]
        worldPos = [0, 0, 0]
        worldOrient = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
        if (not self.placer.ComputeWorldPosition(self.renderer, displayPos, worldPos, worldOrient)):
            return

        lastId = self.placer.GetCellPicker().GetCellId()
        if (lastId == self.lastCellId):
            self.interactor.GetRenderWindow().Render()
            return
        self.lastCellId = lastId
        self.sphere.SetCenter(worldPos)
        self.sphere.Modified()
        self.outputFilter.Update()
        self.appendPolyData.AddInputData(self.outputFilter.GetOutput())

        if not self.renderer.HasViewProp(self.selectedActor):
            self.renderer.AddActor(self.selectedActor)
        self.interactor.GetRenderWindow().Render()

    self.InvokeEvent(vtkCommand.StartInteractionEvent)

    # Call parent function
    # super().OnLeftButtonDown()

  def OnLeftButtonUp(self, obj, event):
    """Left button release.

    Left mouse button release event
    When LMB is released, a EndPickEvent and EndInteractionEvent are emitted
    NOTE: This is different to the C++ class, which emits a SelectionChangedEvent
          instead of an EndPickEvent
    """
    if self.interactor is None or not self.Moving:
      return

    self.Moving = False

    output = self.cleanPolyData.GetOutput()
    self.appendPolyData.SetInputData(output)
    self.interactor.GetRenderWindow().Render()

    self.InvokeEvent(vtkCommand.SelectionChangedEvent)
    self.InvokeEvent(vtkCommand.EndPickEvent)
    self.InvokeEvent(vtkCommand.EndInteractionEvent)

    # Call parent function
    # super().OnLeftButtonUp()

  def OnMouseMove(self, obj, event):
    """On mouse move event."""
    if self.interactor is None or not self.Moving:
      return

    # Get lastest mouse position
    eventPos = self.interactor.GetEventPosition()
    self.EndPosition[0], self.EndPosition[1] = eventPos[0], eventPos[1]
    size = self.interactor.GetRenderWindow().GetSize()
    if self.EndPosition[0] > size[0] - 1:
      self.EndPosition[0] = size[0] - 1
    if self.EndPosition[0] < 0:
      self.EndPosition[0] = 0
    if self.EndPosition[1] > size[1] - 1:
      self.EndPosition[1] = size[1] - 1
    if self.EndPosition[1] < 0:
      self.EndPosition[1] = 0

    # Last and new point
    lastPoint = self.Internal.GetPoint(self.Internal.GetNumberOfPoints() - 1)
    newPoint = self.EndPosition

    # Criteria for enough movement
    if np.linalg.norm(lastPoint - newPoint) > 10:
      # Movement is sufficient
      self.Internal.AddPoint(*newPoint)

      X, Y = self.interactor.GetEventPosition()
      displayPos = [float(X), float(Y)]
      worldPos = [0, 0, 0]
      worldOrient = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
      if (not self.placer.ComputeWorldPosition(self.renderer, displayPos, worldPos, worldOrient)):
        return
      lastId = self.placer.GetCellPicker().GetCellId()
      if (lastId == self.lastCellId):
        return
      self.lastCellId = lastId
      self.sphere.SetCenter(worldPos)
      self.sphere.Modified()
      self.outputFilter.Update()
      # Test appending
      newData = vtkPolyData()
      newData.DeepCopy(self.outputFilter.GetOutput())
      self.appendPolyData.AddInputData(newData)
      self.interactor.GetRenderWindow().Render()
    # Append polydata or add new implicit function
    # Call parent function
    # super().OnMouseMove()

  def __str__(self):
    """Replace PrintSelf in C++ class."""
    indent = 2 * ' '
    s = super().__str__().rstrip() + '\n'
    s += f'{indent}Moving : {self.Moving}\n'
    s += f'{indent}StartPosition: {self.StartPosition[0]}, {self.StartPosition[1]}\n'
    s += f'{indent}EndPosition: {self.EndPosition[0]}, {self.EndPosition[1]}\n'
    return s
