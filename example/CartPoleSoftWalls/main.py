# Add to path temporarily since it hasn't been installed
import os
import sys
sys.path.insert(0, os.path.abspath('../build/python'))

import numpy as np
from pyconpt import opt

cartpole = opt.CartPole()
