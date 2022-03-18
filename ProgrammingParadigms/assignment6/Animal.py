from AnimalBehavior import *
from AnimalStates import *
from random import randint

class Animal:
    def __init__(self):
        self.content = Content(self)
        self.engorged = Engorged(self)
        self.hungry = Hungry(self)

        self.animalType = None
        self.segments = []
        self.animalState = self.content

    def setBehavSnake(self):
        self.animalType = Snake()

    def setBehavCaterpillar(self):
        self.animalType = Caterpillar()

    def setBehavWorm(self):
        self.animalType = Worm()

    def set_state(self, new_state):
        self.animalState = new_state

    def getContentState(self):
        return self.content

    def getEngorgedState(self):
        return self.engorged

    def getHungryState(self):
        return self.hungry

    def setStartingPosition(self, width, height):
        self.segments = [[randint(1, width), randint(1, height)]]

    def move(self, nextHead):
        self.animalState.move(nextHead)

    def eat(self, nextHead):
        self.animalState.eat(nextHead)

    def getSpeed(self):
        return self.animalState.modifySpeed(self.animalType.getSpeed())

    def explain(self):
        return self.animalState.explain()

    def getX(self):
        return self.segments[0][0]

    def getY(self):
        return self.segments[0][1]
