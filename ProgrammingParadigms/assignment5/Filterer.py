from abc import ABC, abstractmethod

class Filterer(ABC):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def filter(self):
        pass

class RemoveAllAbove(Filterer):
    def filter(self, data, maximum):
        newdata = []
        for item in data:
            if item < maximum:
                newdata.append(item)
        return newdata

class RemoveAllBelow(Filterer):
    def filter(self, data, minimum):
        newdata = []
        for item in data:
            if item > minimum:
                newdata.append(item)
        return newdata


