import vtk

from reader import TestReader

def callback(caller, event):
    print(event)
    
fileName = "./sphere.ply"
sphere = vtk.vtkSphereSource()
writer = vtk.vtkPLYWriter()
writer.SetFileName(fileName)
writer.SetInputConnection(sphere.GetOutputPort())
writer.Write()

reader = TestReader()
reader.SetFileName(fileName)
#reader.SetFileName("./nonexisting.ply")

# Add an observer to the executive (pipeline) of the reader
reader.AddObserver(vtk.vtkCommand.AnyEvent, callback)

# Update the information
reader.UpdateInformation()

# We have no data before the Update()
output_info = reader.GetOutputInformation(0)
print(output_info)
if (output_info.Get(TestReader.NUMBER_OF_CELLS()) > 0):
  reader.Update()
else:
  print("No data - no need to call Update()")
print(reader.GetOutput().GetNumberOfPoints())


