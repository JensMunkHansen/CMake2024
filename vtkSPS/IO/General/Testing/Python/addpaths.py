#!/usr/bin/env python
"""Update system path."""
import sys
import os

# Home-made additions to VTK
filedir = os.path.dirname(os.path.realpath(__file__))
if os.name == "posix":
  filepath = os.path.join(filedir, 4*"../" + "build/lib/python%d.%d/site-packages" % (sys.version_info.major, sys.version_info.minor))
  sys.path.insert(0, filepath)
else:
  filepath = os.path.join(filedir, "../../../../build/bin/Lib/site-packages")
  sys.path.insert(0, filepath)
