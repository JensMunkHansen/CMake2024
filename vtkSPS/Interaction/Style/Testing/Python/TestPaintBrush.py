import addpaths

#from spsmodules.spsInteractionStyle import spsPaintBrush
from spsmodules.spsInteractionStyle import spsInteractorStyleDemo as spsPaintBrush
from spsmodules.util.scene_utils import vtk_fps_counter

# noinspection PyUnresolvedReferences
import vtkmodules.vtkInteractionStyle
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.vtkRenderingCore import (
    vtkActor,
    vtkPolyDataMapper,
    vtkRenderWindow,
    vtkRenderWindowInteractor,
    vtkRenderer)
from vtkmodules.vtkFiltersSources import vtkSphereSource
from vtkmodules.vtkCommonTransforms import vtkTransform

import numpy as np

def create_sphere_source():
    # Create a sample mesh, like a sphere
    sphere = vtkSphereSource()
    sphere.SetThetaResolution(300)
    sphere.SetPhiResolution(300)
    return sphere

# Create a renderer, render window, and interactor
renderer = vtkRenderer()
render_window = vtkRenderWindow()
render_window.AddRenderer(renderer)

interactor = vtkRenderWindowInteractor()
interactor.SetRenderWindow(render_window)

# Create multiple sphere actors
for _ in range(1):
    sphere_source = create_sphere_source()
    sphere_source.SetRadius(1)
    sphere_source.Update()
    print(sphere_source.GetOutput().GetNumberOfCells())
    mapper = vtkPolyDataMapper()
    mapper.SetInputConnection(sphere_source.GetOutputPort())

    actor = vtkActor()
    actor.SetMapper(mapper)
    
    # Position actors randomly for demonstration
    actor.SetPosition(np.random.uniform(-1, 1), np.random.uniform(-1, 1), 0)

    tf = vtkTransform()
    tf.RotateX(4)
    tf.Translate(1,2,3)
    actor.SetUserTransform(tf)
    
    # Add the actor to the renderer
    renderer.AddActor(actor)

# Set the background color
renderer.SetBackground(0.1, 0.2, 0.4)

paintBrushStyle = spsPaintBrush()
paintBrushStyle.SetBrushRadius(0.2)
paintBrushStyle.SetResolution(10);
interactor.SetInteractorStyle(paintBrushStyle)

# Start the rendering loop
render_window.Render()
interactor.Initialize()
fpsCounter = vtk_fps_counter(renderer)
interactor.Start()

