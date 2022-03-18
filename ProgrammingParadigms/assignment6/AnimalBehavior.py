# Animal behavior hierarchies 
from abc import ABC, abstractmethod

class AnimalBehavior(ABC): 
    def __init__(self):
        super().__init__()
            
    @abstractmethod
    def getColor(self):
        pass

    @abstractmethod
    def getSpeed(self):
        pass

    @abstractmethod
    def getFood(self):
        pass
        
class Snake(AnimalBehavior): 
    def getColor(self):
        return "green"
    def getSpeed(self):
        return 0.5
    def getFood(self):
        return "red"

class Caterpillar(AnimalBehavior): 
    def getColor(self):
        return "red"
    def getSpeed(self):
        return 1.0
    def getFood(self):
        return "green"
		
class Worm(AnimalBehavior): 
    def getColor(self):
        return "brown"
    def getSpeed(self):
        return 1.5
    def getFood(self):
        return "yellow"
