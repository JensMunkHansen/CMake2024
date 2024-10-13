#!/usr/bin/env python
"""Update system path."""
import sys
import os

# Home-made additions to VTK
filedir = os.path.dirname(os.path.realpath(__file__))
filepath = os.path.join(filedir, 4*"../")
sys.path.insert(0, filepath)

import spspython
