import sys

if sys.version_info < (3,5):
  raise Exception("Unsupported python version")
else:
  # TODO: Do something similar to VTK
  import importlib
  # import vtkmodules.all
  all_m = importlib.import_module('spsmodules.all')

  # import spsmodules
  spsmodules_m = importlib.import_module('spsmodules')

  # make spsmodules.all act as the spsmodules package to support importing
  # other modules from spsmodules package via `vtk`.
  all_m.__path__ = spsmodules_m.__path__
  all_m.__version__ = spsmodules_m.__version__

  # replace old `sps` module with the `all` package.
  sys.modules[__name__] = all_m
