import numpy as np

class uni_elt:
    def __init__(self, size, parent):
        self.size = size
        self.parent = parent

class universe:
    def __init__(self, num_elements):
        self.elts = []
        self.num_sets = num_elements
        
        for i in range(num_elements):
            self.elts.append(uni_elt(1, i))
    
    def find(self, x):
        if (self.elts[x].parent != x):
            self.elts[x].parent = self.find(self.elts[x].parent)
        
        return  self.elts[x].parent
    
    def size(self, x):
        return  self.elts[self.find(x)].size
    
    def join(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if (x == y):    return
        if (self.elts[x].size < self.elts[y].size):
            x, y = y, x
        
        self.elts[y].parent = x
        self.elts[x].size  += self.elts[y].size
        
        self.num_sets -= 1

if  __name__ == '__main__':
    U = universe(5)
    U.join(0, 3)
    U.join(1, 4)
    U.join(1, 2)

    print(U.find(2))
