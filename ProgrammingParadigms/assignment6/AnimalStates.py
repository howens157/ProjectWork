from abc import ABC, abstractmethod

class AnimalState(ABC):
    def __init__(self, animal):
        super().__init__()
        self.animal = animal
        self.stepsTaken = 0
        self.foodEaten = 0

    @abstractmethod
    def move(self, nextHead):
        pass

    @abstractmethod
    def eat(self, nextHead):
        pass

    @abstractmethod
    def modifySpeed(self, baseSpeed):
        pass

    @abstractmethod
    def explain(self):
        pass

class Content(AnimalState):
    def __init__(self, animal):
        super().__init__(animal)

    def move(self, nextHead):
        self.animal.segments.insert(0, nextHead)
        self.animal.segments.pop()
        self.stepsTaken += 1
        if self.stepsTaken is 20:
            self.stepsTaken = 0
            self.foodEaten = 0
            self.animal.set_state(self.animal.getHungryState())
    
    def eat(self, nextHead):
        self.animal.segments.insert(0, nextHead)

        self.stepsTaken = 0
        self.foodEaten += 1
        if self.foodEaten is 3:
            self.stepsTaken = 0
            self.foodEaten = 0
            self.animal.set_state(self.animal.getEngorgedState())

    def modifySpeed(self, baseSpeed):
        return baseSpeed

    def explain(self):
        return "I am content"

class Engorged(AnimalState):
    def __init__(self, animal):
        super().__init__(animal)

    def move(self, nextHead):
        self.animal.segments.insert(0, nextHead)
        self.animal.segments.pop()

        self.stepsTaken += 1
        if self.stepsTaken is 20:
            self.stepsTaken = 0
            self.foodEaten = 0
            self.animal.set_state(self.animal.getContentState())

    def eat(self, nextHead):
        self.animal.segments.insert(0, nextHead)
        self.foodEaten += 1
        self.stepsTaken = 0

    def modifySpeed(self, baseSpeed):
        return baseSpeed*2.0

    def explain(self):
        return "I am engorged!"


class Hungry(AnimalState):
    def __init__(self, animal):
        super().__init__(animal)

    def move(self, nextHead):
        self.animal.segments.insert(0, nextHead)
        self.animal.segments.pop()
        self.stepsTaken += 1
    
    def eat(self, nextHead):
        self.animal.segments.insert(0, nextHead)
        self.foodEaten += 1
        if self.foodEaten is 5:
            self.stepsTaken = 0
            self.foodEaten = 0
            self.animal.set_state(self.animal.getEngorgedState())

    def modifySpeed(self, baseSpeed):
        return baseSpeed/2.0

    def explain(self):
        return "I am hungry!"
