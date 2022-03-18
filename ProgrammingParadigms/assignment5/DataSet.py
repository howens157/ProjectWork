from Sorter import *
from Filterer import *
from Averager import *

class DataSet:
    def __init__(self, sorter, filterer, averager, data):
        self.sorter = sorter
        self.filterer = filterer
        self.averager = averager
        self.data = data

    def sort(self):
        self.data = self.sorter.sort(self, self.data)
        
    def filter(self, value):
        self.data = self.filterer.filter(self, self.data, value)

    def average(self):
        return self.averager.average(self, self.data)
