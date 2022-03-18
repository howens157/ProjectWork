from abc import ABC, abstractmethod

class Averager(ABC):
    def __init__(self):
        super().__init__()

    @abstractmethod
    def average(self):
        pass

class Mean(Averager):
    def average(self, data):
        return sum(data)/len(data)

class Median(Averager):
    def average(self, data):
        head = 0
        tail = len(data)-1
        while True:
            if head is tail:
                return data[head]
            elif head is tail-1:
                return ((data[head] + data[tail])/2)
            head += 1
            tail -= 1

class Mode(Averager):
    def average(self, data):
        modes = []
        counts = {}
        highestCount = 0
        for item in data:
            if item in counts.keys():
                counts[item] += 1
            else:
                counts[item] = 1
            if counts[item] > highestCount:
                highestCount = counts[item]

        for key in counts:
            if counts[key] is highestCount:
                modes.append(key)

        return modes
            
