# !/usr/bin/env python
# -*- coding: utf-8 -*-
import sys

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
# noinspection PyUnresolvedReferences
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkCommonCore import (
  vtkCommand,
)
from vtkmodules.vtkCommonDataModel import vtkPlanes
from vtkmodules.vtkFiltersCore import vtkClipPolyData, vtkAppendPolyData
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkInteractionStyle import vtkInteractorStyleTrackballCamera
from vtkmodules.vtkInteractionWidgets import vtkBoxWidget2
from vtkmodules.vtkIOPLY import vtkPLYWriter
from vtkmodules.vtkIOLegacy import vtkPolyDataReader
from vtkmodules.vtkIOXML import vtkXMLPolyDataReader
from vtkmodules.vtkIOGeometry import (
  vtkBYUReader,
  vtkSTLReader,
  vtkOBJReader
)

from vtkmodules.vtkRenderingCore import (
  vtkActor,
  vtkDataSetMapper,
  vtkRenderWindow,
  vtkRenderWindowInteractor,
  vtkRenderer
)

class vtkPolyDataReaderFactory:
  def __new__(cls):
    raise TypeError("Static classes cannot be instantiated")
  @staticmethod
  def CreateReader(inputFileName):
    fileName, fileExtension = os.path.splitext(inputFileName)
    if fileExtension in ['.ply', '.PLY']:
      reader = vtkPLYReader()
    elif fileExtension in ['.vtp', '.VTP']:
      reader = vtkXMLPolyDataReader()
    elif fileExtension in ['.stl', '.STL']:
      reader = vtkSTLReader()
    elif fileExtension in ['.vtk', '.VTK']:
      reader = vtkPolyDataReader()
    elif fileExtension in ['.g', '.G']:
      reader = vtkBYUReader()
    elif fileExtension in ['.obj', '.OBJ']:
      reader = vtkOBJReader()
    else:
      raise NameError("Filetype not supported")
    if not os.path.exists(inputFileName):
      raise IOError("File: %s does not exist" % (inputFileName))
    reader.SetFileName(inputFileName)
    return reader
  @staticmethod
  def SupportedExtensions():
    return [".ply", ".vtp", ".stl", ".vtk", ".g", ".obj"]
  @staticmethod
  def CreateReaders(inputFileNames, append=False):
    readers = []
    for inputFileName in inputFileNames:
      if not os.path.exists(inputFileName):
        raise Exception("File: %s does not exist" % (inputFileName))
      readers.append(vtkPolyDataReaderFactory.CreateReader(inputFileName))
    if not append:
      return readers
    else:
      append = vtkAppendPolyData()
      for reader in readers:
        append.AddInputConnection(reader.GetOutputPort())
      return append

class Cutter:
    def __init__(self):
        self.clipperPoly = None
        pass
    def SetClipper(self, clipper: vtkClipPolyData):
        self.clipperPoly = clipper
    
    def interactionFcn(self, caller, event):
      boxWidget = caller
      planesClipping = vtkPlanes()
      boxWidget.GetRepresentation().GetPlanes(planesClipping)
      #get the planes
      if (self.clipperPoly is not None):
          self.clipperPoly.SetClipFunction(planesClipping)
          self.clipperPoly.InsideOutOn()
    def saveFcn(self, caller, event):
      if caller.GetKeySym() == 'o':
        if (self.clipperPoly is not None):
          writer = vtkPLYWriter()
          writer.SetFileName("out.ply")
          writer.SetInputConnection(self.clipperPoly.GetOutputPort())
          writer.Write()

def main(argv):
  # Box widget
  boxWidget = vtkBoxWidget2()

  if len(argv) > 1:
    source = vtkPolyDataReaderFactory.CreateReader(argv[1])
    source.Update()
  else:
    # Create a sphere
    source = vtkSphereSource()
    source.SetThetaResolution(32)
    source.SetPhiResolution(32)
    source.Update()
  
  # storing planes of the bounding box
  planesClipping = vtkPlanes()
  boxWidget.GetRepresentation().GetPlanes(planesClipping)
  
  # clipping structure
  clipperPoly = vtkClipPolyData()
  clipperPoly.SetInputConnection(source.GetOutputPort())
  clipperPoly.SetClipFunction(planesClipping)
  
  #mapper
  selectMapper = vtkDataSetMapper()
  selectMapper.SetInputConnection(clipperPoly.GetOutputPort())
  selectMapper.Update()
  
  #actor
  selectActor = vtkActor()
  selectActor.GetProperty().SetColor(1.0000, 0.3882, 0.2784)
  selectActor.SetMapper(selectMapper)

  cutter = Cutter()
  cutter.SetClipper(clipperPoly)
  
  # Create graphics stuff
  ren1 = vtkRenderer()
  ren1.SetBackground(.2, .2, .25)
  
  renWin = vtkRenderWindow()
  renWin.AddRenderer(ren1)
  renWin.SetSize(512, 512)
  
  # window interactor
  windowInteractor =  vtkRenderWindowInteractor()
  windowInteractor.SetRenderWindow(renWin)
  cameraStyle = vtkInteractorStyleTrackballCamera()
  windowInteractor.SetInteractorStyle(cameraStyle)
  windowInteractor.AddObserver(vtkCommand.KeyPressEvent, cutter.saveFcn)
  
  #the box widget
  boxWidget.SetInteractor(windowInteractor)
  boxWidget.GetRepresentation().SetPlaceFactor(1) # Default is 0.5
  boxWidget.GetRepresentation().PlaceWidget(selectActor.GetBounds())
  boxWidget.On()

  boxWidget.AddObserver(vtkCommand.InteractionEvent, cutter.interactionFcn)
  
  # Add the actor
  ren1.AddActor(selectActor)
  
  # Generate a camera
  ren1.ResetCamera()
  
  windowInteractor.Initialize()
  windowInteractor.Start()

if __name__ == "__main__":
  main(sys.argv)

# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
