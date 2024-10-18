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
        # Create a custom key "NUMBER_OF_CELLS" for propagating information about content downstream during
        # RequestInformation
        if TestReader._NUMBER_OF_CELLS is None:
            # 1. Use keys.MakeKey
            # TestReader._NUMBER_OF_CELLS = ???

            # Bug in VTK python wrapper (double deletion)
            if (TestReader._NUMBER_OF_CELLS.GetReferenceCount() < 2):
                TestReader._NUMBER_OF_CELLS.SetReferenceCount(2)
        self._reader = vtk.vtkPLYReader();
        self._fileName = ""
    def RequestData(self, request, inInfo, outInfo):
        # Here we should only have read the reminder of the file (or stream)
        output = vtk.vtkPolyData.GetData(outInfo)
        # DeepCopy the output from the ply reader to the output
        return 1
    def RequestInformation(self, request, inInfo, outInfo):
        info = outInfo.GetInformationObject(0)
        nCells = 0

        # 2. Find a way of getting the number of cells (pretend that
        # we read them from a header).

        # nCells = ?
        
        # Set information for downstream consumers (syntax is reversed)
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
