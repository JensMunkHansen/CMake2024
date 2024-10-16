import addpaths

from spsmodules.spsFiltersGeneral import spsDistancePolyDataFilter

import vtk

smp = vtk.vtkSMPTools()
smp.SetBackend("TBB")

# Create two spheres
#sphere1 = vtk.vtkSphereSource()
#sphere1.SetCenter(0, 0, 0)
#sphere1.SetPhiResolution(20)
#sphere1.SetThetaResolution(20)
#sphere1.SetRadius(5)

reader1 = vtk.vtkPLYReader()
reader1.SetFileName("./01_lowerJawScan.ply")
reader1.Update()

#sphere2 = vtk.vtkSphereSource()
#sphere2.SetCenter(0, 0, 0)  # Initially offset second sphere
#sphere2.SetPhiResolution(20)
#sphere2.SetThetaResolution(20)
#sphere2.SetRadius(5)

reader2 = vtk.vtkPLYReader()
reader2.SetFileName("./01_upperJawScan.ply")
reader2.Update()

dec1 = vtk.vtkQuadricDecimation()
dec1.SetInputConnection(reader1.GetOutputPort())
dec2 = vtk.vtkQuadricDecimation()
dec2.SetInputConnection(reader2.GetOutputPort())

dec1.SetTargetReduction(0.96)
dec2.SetTargetReduction(0.96)

# Calculate the distance between two polydata objects
distanceFilter = spsDistancePolyDataFilter()
distanceFilter.SetInputConnection(0, dec1.GetOutputPort())
distanceFilter.SetInputConnection(1, dec2.GetOutputPort())
distanceFilter.ComputeCellCenterDistanceOn()
distanceFilter.SignedDistanceOn()
distanceFilter.Update()

# Create a mapper and actor for the first sphere
mapper1 = vtk.vtkPolyDataMapper()
mapper1.SetInputConnection(reader2.GetOutputPort())
actor1 = vtk.vtkActor()
actor1.SetMapper(mapper1)
#actor1.GetProperty().SetColor(1, 0, 0)  # Red for the first sphere

# Create a mapper and actor for the second sphere (distance colored)
mapper2 = vtk.vtkPolyDataMapper()
mapper2.SetInputConnection(distanceFilter.GetOutputPort())
mapper2.ScalarVisibilityOn()
mapper2.SetScalarRange(distanceFilter.GetOutput().GetPointData().GetScalars().GetRange())  # Distance-based coloring
scalars = distanceFilter.GetOutput().GetPointData().GetScalars() 
rng = [scalars.GetRange()[0],
       scalars.GetRange()[1]]
lim = max([abs(v) for v in rng])
mapper2.SetScalarRange(-lim, lim)


actor2 = vtk.vtkActor()
actor2.SetMapper(mapper2)

tf1 = vtk.vtkTransform()
tf1.SetMatrix(actor1.GetMatrix())
tf2 = vtk.vtkTransform()
tf2.SetMatrix(actor2.GetMatrix())

tf12 = vtk.vtkTransform()
tf12.Concatenate(tf1)
tf12.Concatenate(tf2.GetInverse())

distanceFilter.GetTransform().SetInput(tf12)

# Create a renderer, render window, and interactor
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Add actors to the renderer
renderer.AddActor(actor1)
renderer.AddActor(actor2)
renderer.SetBackground(0.1, 0.2, 0.3)  # Background color

# Set up interactor style to allow dragging of objects
#style = vtk.vtkInteractorStyleTrackballActor()
#renderWindowInteractor.SetInteractorStyle(style)

# Define a callback to update the distance filter when sphere2 moves
class MoveCallback:
    def __init__(self, sphereSource, distanceFilter, actor, mapper):
        self.sphereSource = sphereSource
        self.distanceFilter = distanceFilter
        self.actor = actor
        self.mapper = mapper

    def __call__(self, obj, event):
        if (type(renderWindowInteractor.GetInteractorStyle().GetCurrentStyle()) == vtk.vtkInteractorStyleJoystickActor or
            type(renderWindowInteractor.GetInteractorStyle().GetCurrentStyle()) == vtk.vtkInteractorStyleTrackballActor):
          tf1.SetMatrix(actor1.GetMatrix())
          tf2.SetMatrix(actor2.GetMatrix())
          distanceFilter.GetTransform().Update()
          self.distanceFilter.Update()
          scalars = distanceFilter.GetOutput().GetPointData().GetScalars() 
          rng = [scalars.GetRange()[0],
                 scalars.GetRange()[1]]
          lim = max([abs(v) for v in rng])
          self.mapper.SetScalarRange(-lim, lim)
          self.actor.GetMapper().Modified()
          obj.GetRenderWindow().Render()

# Create a callback to update the distance filter when moving the second sphere
callback = MoveCallback(reader2, distanceFilter, actor2, mapper2)

renderWindowInteractor.AddObserver("EndInteractionEvent", callback)

# Start the interaction
renderWindow.Render()
renderWindowInteractor.Start()
