import addpaths

from spsmodules.spsFiltersGeneral import spsDistancePolyDataFilter

import vtk

smp = vtk.vtkSMPTools()
smp.SetBackend("TBB")

# Create two spheres
sphere1 = vtk.vtkSphereSource()
sphere1.SetCenter(0, 0, 0)
sphere1.SetPhiResolution(50)
sphere1.SetThetaResolution(50)
sphere1.SetRadius(5)
sphere1.Update()

sphere2 = vtk.vtkSphereSource()
sphere2.SetCenter(0, 0, 0)  # Initially offset second sphere
sphere2.SetPhiResolution(50)
sphere2.SetThetaResolution(50)
sphere2.SetRadius(5)
sphere2.Update()
    
# Calculate the distance between two polydata objects
distanceFilter = spsDistancePolyDataFilter()
distanceFilter.SetInputData(0, sphere1.GetOutput())
distanceFilter.SetInputData(1, sphere2.GetOutput())
#distanceFilter.ComputeCellCenterDistanceOn()
distanceFilter.SignedDistanceOn()
distanceFilter.Update()

# Create a mapper and actor for the first sphere
mapper1 = vtk.vtkPolyDataMapper()
mapper1.SetInputConnection(sphere1.GetOutputPort())
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
style = vtk.vtkInteractorStyleTrackballActor()
renderWindowInteractor.SetInteractorStyle(style)

# Define a callback to update the distance filter when sphere2 moves
class MoveCallback:
    def __init__(self, sphereSource, distanceFilter, actor, mapper):
        self.sphereSource = sphereSource
        self.distanceFilter = distanceFilter
        self.actor = actor
        self.mapper = mapper

    def __call__(self, obj, event):
        self.sphereSource.Update()
        distanceFilter.GetTransform().SetMatrix(actor1.GetMatrix())
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
callback = MoveCallback(sphere2, distanceFilter, actor2, mapper2)
renderWindowInteractor.AddObserver("EndInteractionEvent", callback)

# Start the interaction
renderWindow.Render()
renderWindowInteractor.Start()
