import os
import vtk
from vtk.util.vtkAlgorithm import VTKPythonAlgorithmBase
from vtk.util import keys

class TestReader(VTKPythonAlgorithmBase):
    @staticmethod
    def NUMBER_OF_CELLS():
        return TestReader._NUMBER_OF_CELLS
    def __init__(self):
        VTKPythonAlgorithmBase.__init__(self,
            nInputPorts=0,
            nOutputPorts=1, outputType='vtkPolyData')
        # Custom key for propagating information during RequestInformation
        if TestReader._NUMBER_OF_CELLS is None:
            TestReader._NUMBER_OF_CELLS = keys.MakeKey(keys.IntegerKey, "NUMBER_OF_CELLS", "TestReader")
            # Bug in VTK python wrapper
            if (TestReader._NUMBER_OF_CELLS.GetReferenceCount() < 2):
                TestReader._NUMBER_OF_CELLS.SetReferenceCount(2)
        self._reader = vtk.vtkPLYReader();
        self._fileName = ""
    def RequestData(self, request, inInfo, outInfo):
        # Here we should only have read the reminder of the file (or stream)
        if os.path.exists(self._fileName):
            self._reader.Update()
            output = vtk.vtkPolyData.GetData(outInfo)
            polyData = self._reader.GetOutput()
            if (polyData.GetNumberOfPoints() > 0):
                output.DeepCopy(polyData)
                return 1
            else:
                return 0
        return 0
    def RequestInformation(self, request, inInfo, outInfo):
        info = outInfo.GetInformationObject(0)
        nCells = 0
        if os.path.exists(self._fileName):
            # We anticipate that we could read header information and know the number of cells
            # Here we just read entire file
            self._reader.Update()
            nCells = self._reader.GetOutput().GetNumberOfCells()
        # Set information for downstream consumers (we could also emit an event)
        TestReader._NUMBER_OF_CELLS.Set(info, int(nCells))
        return 1
    def GetOutput(self):
        return self.GetOutputDataObject(0)
    def SetFileName(self, fname):
        if fname != self._fileName:
            self._fileName = fname
            self._reader.SetFileName(self._fileName)
            self.Modified()

    def GetFileName(self):
        return self._fileName
    
TestReader._NUMBER_OF_CELLS = None
