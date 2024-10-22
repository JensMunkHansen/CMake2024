# Custom filters that we could create
# from tsmodules.util.io import vtkPolyDataReaderFactory
# from tsmodules.tsFiltersGeneral import tsDistancePolyDataFilter

####################################################################
# Explicit import of needed modules. Can be replaced with importing
# all modules, i.e. import vtk
####################################################################

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkCommonColor import vtkNamedColors
from vtkmodules.vtkCommonCore import vtkSMPTools
from vtkmodules.vtkCommonDataModel import vtkBox
from vtkmodules.vtkFiltersCore import (
  vtkAppendPolyData,
  vtkClipPolyData,
  vtkPolyDataNormals,
  vtkThreshold,
  vtkTriangleFilter,
  vtkQuadricDecimation)
from vtkmodules.vtkFiltersGeneral import vtkDistancePolyDataFilter
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkIOPLY import vtkPLYWriter

from vtkmodules.vtkRenderingCore import (
  vtkActor,
  vtkCamera,
  vtkPolyDataMapper,
  vtkRenderWindow,
  vtkRenderWindowInteractor,
  vtkRenderer)
from vtkmodules.vtkRenderingAnnotation import vtkScalarBarActor
