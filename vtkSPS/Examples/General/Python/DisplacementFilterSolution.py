from vtkmodules.util.vtkAlgorithm import (
    VTKPythonAlgorithmBase
)
from vtkmodules.vtkCommonDataModel import (
    vtkPolyData
)
from vtkmodules.vtkCommonCore import (
    reference,
    vtkDoubleArray
)
from vtkmodules.vtkFiltersCore import (
  vtkImplicitPolyDataDistance
)

# Most complex cell type supported
VTK_MAXIMUM_NUMBER_OF_POINTS = 216

class DisplacementPolyDataFilter(VTKPythonAlgorithmBase):
    def __init__(self):
        VTKPythonAlgorithmBase.__init__(self,
            nInputPorts=2,
            nOutputPorts=2, outputType='vtkPolyData')
        self.Gradient = 0
        self.ComputeSecondDisplacement = 1
        self.ComputeCellCenterDisplacement = 0
        self.SignedDistance = 1
        self.NegateDistance = 0
    def SetSignedDistance(self, signedDistance):
        self.Signeddistance = signedDistance
        self.Modified()
    def SignedDistanceOn(self):
        self.SetSignedDistance(1)
    def SignedDistanceOff(self):
        self.SetSignedDistance(0)
    def SetComputeCellCenterDisplacement(self, arg):
        self.ComputeCellCenterDisplacement = arg
        self.Modified()
    def ComputeCellCenterDisplacementOn(self):
        self.SetComputeCellCenterDisplacement(1)
    def ComputeCellCenterDisplacementOff(self):
        self.SetComputeCellCenterDisplacement(0)
    def SetNegateDistance(self, negateDistance):
        self.NegateDistance = negateDistance
        self.Modified()
    def NegateDistanceOn(self):
        self.SetNegateDistance(1)
    def NegateDistanceOff(self): 
        self.SetNegateDistance(0)
    def SetGradient(self, gradient):
        self.Gradient = gradient
        self.Modified()
    def GradientOn(self):
        self.SetGradient(1)
    def GradientOff(self):
        self.SetGradient(0)
    def GetOutput(self, port=0):
        return self.GetOutputDataObject(port)
    def RequestData(self, request, inputVector, outputVector):
        print("RequestData")
        input0 = vtkPolyData.GetData(inputVector[0], 0)
        input1 = vtkPolyData.GetData(inputVector[1], 0)
        output0 = vtkPolyData.GetData(outputVector, 0)
        output1 = vtkPolyData.GetData(outputVector, 1)

        output0.CopyStructure(input0)
        output0.GetPointData().PassData(input0.GetPointData())
        output0.GetCellData().PassData(input0.GetCellData())
        output0.BuildCells()
        self.GetPolyDataDistance(output0, input1)

        if (self.ComputeSecondDisplacement):
            output1.CopyStructure(input1)
            output1.GetPointData().PassData(input1.GetPointData())
            output1.GetCellData().PassData(input1.GetCellData())
            output1.BuildCells()
            self.GetPolyDataDistance(output1, input0)
        return 1

    def GetPolyDataDistance(self, mesh, src):
        if (mesh.GetNumberOfCells() == 0 or mesh.GetNumberOfPoints() == 0):
            print("No points/cells to operate on")
            return

        if (src.GetNumberOfPolys() == 0 or src.GetNumberOfPoints() == 0):
            print("No points/cells to difference from")
            return

        imp = vtkImplicitPolyDataDistance()
        imp.SetInput(src)

        # Calculate distance from points.
        numPts = mesh.GetNumberOfPoints()

        directionArray = vtkDoubleArray()
        directionArray.SetName("Direction")
        directionArray.SetNumberOfComponents(3)
        directionArray.SetNumberOfTuples(numPts)

        distanceArray = vtkDoubleArray()
        distanceArray.SetName("Distance")
        distanceArray.SetNumberOfComponents(1)
        distanceArray.SetNumberOfTuples(numPts)

        # The sign of the functions are the dot product between pseudo normal and the vector
        # x-p. The point p is on the target polydata.
        for ptId in range(numPts):
            if (self.Gradient):
                pt = mesh.GetPoint(ptId)
                gradient = [0,0,0]
                val = imp.EvaluateFunction(pt)
                imp.EvaluateGradient(pt, gradient)
                dist = (-val if self.NegateDistance else val) if self.SignedDistance else abs(val)
                directionArray.SetTuple(ptId, gradient)
                distanceArray.SetValue(ptId, dist)
            else:
                pt = mesh.GetPoint(ptId)
                closestPoint = [0,0,0]
                val = imp.EvaluateFunctionAndGetClosestPoint(pt, closestPoint)
                dist = (-val if self.NegateDistance else val) if self.SignedDistance else abs(val)
                direction = [0,0,0]
                absDistance = 0.0
                for i in range(3):
                    direction[i] = closestPoint[i] - pt[i]
                absDistance = max(1e-6, abs(dist))
                for i in range(3):
                    direction[i] /= absDistance
      
                directionArray.SetTuple(ptId, direction)
                distanceArray.SetValue(ptId, dist)

        mesh.GetPointData().AddArray(directionArray)
        mesh.GetPointData().AddArray(distanceArray)
        mesh.GetPointData().SetActiveVectors("Direction")
        mesh.GetPointData().SetActiveScalars("Distance")

        # Calculate distance from cell centers.
        if (self.ComputeCellCenterDisplacement):
            numCells = mesh.GetNumberOfCells()

            cellDirectionArray = vtkDoubleArray()
            cellDirectionArray.SetName("Direction")
            cellDirectionArray.SetNumberOfComponents(3)
            cellDirectionArray.SetNumberOfTuples(numCells)

            cellDistanceArray = vtkDoubleArray()
            cellDistanceArray.SetName("Distance")
            cellDistanceArray.SetNumberOfComponents(1)
            cellDistanceArray.SetNumberOfTuples(numCells)

            weights = VTK_MAXIMUM_NUMBER_OF_POINTS*[0]
            for cellId in range(numCells):
                cell = mesh.GetCell(cellId)
                subId = reference(0)
                pcoords = [0,0,0]
                x = [0,0,0]

                cell.GetParametricCenter(pcoords)
                cell.EvaluateLocation(subId, pcoords, x, weights)

                if self.Gradient:
                    gradient = [0,0,0]
                    imp.EvaluateGradient(x, gradient)
                    val = imp.EvaluateFunction(x)
                    dist = (-val if self.NegateDistance else val) if self.SignedDistance else abs(val)
                    cellDirectionArray.SetTuple(cellId, gradient)
                    cellDistanceArray.SetValue(cellId, dist)
                else:
                    # Displacement
                    closestPoint = [0,0,0]
                    val = imp.EvaluateFunctionAndGetClosestPoint(x, closestPoint)
                    dist = (-val if self.NegateDistance else val) if self.SignedDistance else abs(val)
                    direction = 3 * [0]
                    for i in range(3):
                        direction[i] = closestPoint[i] - x[i] # original
                    absDistance = max(1e-6, abs(dist))
                    for i in range(3):
                        direction[i] /= absDistance
                    cellDirectionArray.SetTuple(cellId, direction)
                    cellDistanceArray.SetValue(cellId, dist)

            mesh.GetCellData().AddArray(cellDirectionArray)
            mesh.GetCellData().AddArray(cellDistanceArray)

            mesh.GetCellData().SetActiveVectors("Direction")
            mesh.GetCellData().SetActiveScalars("Distance")

        def GetSecondDistanceOutput(self):
            if (not self.ComputeSecondDisplacement):
                return None
            return vtkPolyData.SafeDownCast(self.GetOutputDataObject(1))

        def PrintSelf(self):
            super(SpsDisplacementPolyDataFilter,self).PrintSelf()
            print("SignedDistance: " + str(self.SignedDistance))
            print("NegateDistance: " + str(self.NegateDistance))
            print("Gradient (instead of gradient): " + str(self.Gradient))
            print("ComputeSecondDisplacement: " + str(self.ComputeSecondDisplacement))
            print("ComputeCellCenterDisplacement: " + str(self.ComputeCellCenterDisplacement))

# Local variables: #
# tab-width: 2 #
# python-indent: 2 #
# indent-tabs-mode: nil #
# End: #
            
