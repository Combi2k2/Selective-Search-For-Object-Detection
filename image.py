import numpy as np

class Image:
    def __init__(self, width, height, val):
        self.width  = width
        self.height = height

        self.data = np.array([val] * width * height)

    def imRef(self, x, y):
        return  self.data[y * self.width + x]