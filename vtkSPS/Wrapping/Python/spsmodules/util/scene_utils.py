#!/usr/bin/env python3
from timeit import default_timer as timer

from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonCore import (
  vtkUnsignedCharArray,
  vtkCommand,  
  vtkRandomPool)
from vtkmodules.vtkCommonDataModel import vtkPolyData
import vtkmodules.vtkRenderingFreeType
from vtkmodules.vtkRenderingCore import (
  vtkRenderWindowInteractor,
  vtkRenderWindow,
  vtkCamera,
  vtkRenderer,
  vtkActor,
  vtkTextActor)

def vtk_subfigs(nrows=1, ncols=1, sharecamera=False):
  renderWindow = vtkRenderWindow()
  renderers = []
  camera = None
  if sharecamera:
    camera = vtkCamera()
  for irow in range(nrows-1,-1,-1):
    for icol in range(ncols):
      renderer = vtkRenderer()
      renderer.SetViewport(0.0 + icol*1.0/ncols,0.0 + irow*1.0/nrows,
                           (icol+1)*1.0/ncols,(irow+1)*1.0/nrows)
      if camera is not None:
        renderer.SetActiveCamera(camera)
      renderWindow.AddRenderer(renderer)
      renderers.append(renderer)
  return renderWindow, renderers

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
    
class vtk_fps_counter:
    def __init__(self, renderer, x=0, y=0):
        self.mRenderer = renderer
        self.mRenderObservationTag = self.mRenderer.AddObserver(vtkCommand.EndEvent, self)
        self.mIren = self.mRenderer.GetRenderWindow().GetInteractor()
        self.mInteractorObservationTag = self.mIren.AddObserver(vtkCommand.TimerEvent, self.interactorCallback)
        # DPI is 72 times the display scaling factor (in VTK)
        dpi = self.mRenderer.GetRenderWindow().GetDPI()
        self.ActorPosX = x
        self.ActorPosY = y
        
        self.mFrameCount    = 0         # Number of frames collected since last FPS was calculated.
        self.mStartTime     = timer()   # The last time FPS was calculated.
        self.mFpsUpdateRate = 1         # How often to update FPS in seconds.
        self.mTickCount     = 0
        self.mSecondaryTime = timer()
        
        self._createFpsTextActor()
    def interactorCallback(self, obj, ev):
        if (self.mTickCount % 15 == 0):
          _currentTime = timer()
          _duration = _currentTime - self.mSecondaryTime
          _fps = 15 / _duration
          self.mSecondaryTime = _currentTime
          self.mFpsActor2.SetInput("FPS: {:.2f}".format(_fps))
        self.mTickCount = self.mTickCount + 1
    def __del__(self):
        self.mRenderer.RemoveObserver(self.mRenderObservationTag)
    def setPosition(self, x, y):
        self.ActorPosX = x
        self.ActorPosY = y
        self.mFpsActor.SetPosition(self.ActorPosX, self.ActorPosY)
    
    def __call__(self, caller, event):
        if event == "EndEvent":
            self.mFrameCount = self.mFrameCount + 1
            
            if timer() - self.mStartTime > self.mFpsUpdateRate:
                _currentTime     = timer()
                _duration        = _currentTime - self.mStartTime
                
                _fps = self.mFrameCount/_duration
                self.mFpsActor.SetInput("FPS: {:.2f}".format(_fps))
                self.mStartTime  = _currentTime
                self.mFrameCount = 0
                
    def _createFpsTextActor(self):
        self.mFpsActor = vtkTextActor()
        self.mFpsActor.GetTextProperty().SetFontFamilyAsString("Georgia")
        self.mFpsActor.GetTextProperty().SetFontSize(30)
        self.mFpsActor.GetTextProperty().SetColor([1, 1, 1])
        self.mFpsActor.SetPosition(self.ActorPosX, self.ActorPosY)
        self.mRenderer.AddActor(self.mFpsActor)      

# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
