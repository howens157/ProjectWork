import tkinter as tk
from AnimalBehavior import *
from Animal import *
import pdb

class Grid:
    def __init__(self, master):
        #Initialize grid
        self.master = master
        self.keypressed=None
        self.food = None
        self.animal = None
        self.afterID = None
        self.foodEaten = 0
        self.score = 0
        self.gameOver = False
        self.moving = False
        self.master.title("Lines")
        self.height = 36 
        self.width = 24 
        self.rectangle_size = 15
        self.canvas = tk.Canvas(width=self.width*self.rectangle_size, 
            height=(self.height*self.rectangle_size)+self.height/2)
        self.drawGrid()
        
        # Initialize buttons in a special button frame at bottom of screen
        self.button_frame = tk.Frame(self.master)
        self.button_frame.pack(side="bottom", fill="x", expand=False)
        self.canvas.pack(side="top", fill="both", expand=True)

        self.stateVar = tk.StringVar()
        self.stateVar.set("Animal's State")
        self.label1 = tk.Label(self.master, textvariable=self.stateVar)
        self.label1.pack()

        self.instruction = tk.StringVar()
        self.instruction.set("Please select an Animal")
        self.label2 = tk.Label(self.master, textvariable=self.instruction)
        self.label2.pack()
        
        ######################################################################
        ## TO DO: Create buttons for caterpillar and worm here.  Add them to the grid.
        ######################################################################
        self.button1 = tk.Button(self.button_frame, text="Snake", command=self.createSnake)
        self.button1.grid(row=0, column=1, sticky="nw")
        self.button2 = tk.Button(self.button_frame, text="Caterpillar", command=self.createCaterpillar)
        self.button2.grid(row=0, column=int(self.width/2), sticky="n")
        self.button3 = tk.Button(self.button_frame, text="Worm", command=self.createWorm)
        self.button3.grid(row=0, column=int(self.width-1), sticky="ne")
        self.button1.pack()
        self.button2.pack()
        self.button3.pack()

        self.canvas.pack()    
        
        ######################################################################
        # bind arrow keys to handlers
        # TO DO: Add Left and Right keypress handlers
        ######################################################################
        master.bind("<Down>", self.handle_down_key)
        master.bind("<Up>", self.handle_up_key)
        master.bind("<Left>", self.handle_left_key)
        master.bind("<Right>", self.handle_right_key)
        
        # ####################################################################
        # IF YOU HAVE TIME replace this coarse-grained update with a more fine-grained change mechanism
        # Your game will be much less jerky if you do that.
        ######################################################################
        self.fillGrid()
       
    def resetGame(self):
        self.fillGrid()
        self.keypressed=None
        self.moving = False
        self.gameOver = False
        self.score = 0
        self.foodEaten = 0
        self.newFood()
        self.drawSnake()

    def newFood(self):
        while True:
            self.food = [randint(1, self.width), randint(1, self.height)]
            if self.food not in self.animal.segments:
                self.placeMarker(self.food[0], self.food[1], self.animal.animalType.getFood())
                break


    # Special move function.  
    # Snakes game requires us to keep moving in one direction until we 
    # press another key (a bit of a pain to figure out)
    # TO DO: You need to make the move method actuall move the snake!
    def move(self):
        if self.animal.animalType != None and not self.gameOver:
            if (self.keypressed == 1):
                nextHead = self.animal.segments[0].copy()
                nextHead[1] -= 1
            elif (self.keypressed == 3):
                nextHead = self.animal.segments[0].copy()
                nextHead[1] += 1
            elif (self.keypressed == 2):
                nextHead = self.animal.segments[0].copy()
                nextHead[0] += 1
            elif (self.keypressed == 4):
                nextHead = self.animal.segments[0].copy()
                nextHead[0] -= 1
            
            if nextHead == self.food:
                self.animal.eat(nextHead)
                self.foodEaten += 1
                self.score += self.foodEaten 
                self.newFood()
                self.drawNewSnake()
                self.stateVar.set(self.animal.explain())
            elif nextHead[0] == 0 or nextHead[0] == self.width+1 or nextHead[1] == 0 or nextHead[1] == self.height+1 or nextHead in self.animal.segments[0:len(self.animal.segments)-1]:
                self.master.after_cancel(self.afterID)
                self.instruction.set(f'Game Over!\nScore: {self.score}\nPlease quit and try again!')
                self.gameOver = True
            else:
                prevTail = self.animal.segments[len(self.animal.segments)-1]
                self.clearMarker(prevTail[0], prevTail[1])
                self.animal.move(nextHead)
                self.drawNewSnake()
                self.stateVar.set(self.animal.explain())

            
        # After 1 second, call scanning again (create a recursive loop)
        # This construct is very important because it allows the system to
        # continually check for keypresses
            self.afterID = self.master.after(int(300*self.animal.getSpeed()), self.move) 

    #######################################################################
    #Handlers for keypresses
    #######################################################################
    def handle_up_key(self,event):
        if self.keypressed != 3 and self.keypressed != 1:
            self.keypressed = 1
            if not self.moving:
                self.move()
                self.moving = True
            
    def handle_right_key(self,event):
        if self.keypressed != 4 and self.keypressed != 2:
            self.keypressed = 2
            if not self.moving:
                self.move()
                self.moving = True
            
    def handle_down_key(self,event):
        if self.keypressed != 1 and self.keypressed != 3:
            self.keypressed = 3
            if not self.moving:
                self.move()
                self.moving = True

    def handle_left_key(self,event):
        if self.keypressed != 2 and self.keypressed != 4:
            self.keypressed = 4
            if not self.moving:
                self.move()
                self.moving = True
        
    ########################################################################
    # Create animals
    # TO DO: Create the two other animals. 
    ########################################################################
    def createSnake(self):
        # Place the 'snake'
        self.animal = Animal()
        self.animal.setBehavSnake()
        self.animal.set_state(self.animal.getContentState()) 
        self.animal.setStartingPosition(self.width,self.height) #Send the dimensions of the grid
        self.resetGame()
        self.instruction.set("Use arrow keys to control!")

    def createCaterpillar(self):
        # Place the 'caterpillar'
        self.animal = Animal()
        self.animal.setBehavCaterpillar() 
        self.animal.set_state(self.animal.getContentState()) 
        self.animal.setStartingPosition(self.width,self.height) #Send the dimensions of the grid
        self.resetGame()
        self.instruction.set("Use arrow keys to control!")

    def createWorm(self):
        # Place the 'worm'
        self.animal = Animal()
        self.animal.setBehavWorm() 
        self.animal.set_state(self.animal.getContentState()) 
        self.animal.setStartingPosition(self.width,self.height) #Send the dimensions of the grid
        self.resetGame()
        self.instruction.set("Use arrow keys to control!")
        
    # Draws the grid
    def drawGrid(self):
        # Creates all vertical lines at intervals of rectangle_size
        for i in range(0, self.width*self.rectangle_size, self.rectangle_size):
            self.canvas.create_line([(i, 0), (i, self.height*self.rectangle_size)])

        # Creates all horizontal lines at intervals of 10
        for i in range(0, self.height*self.rectangle_size, self.rectangle_size):
            self.canvas.create_line([(0, i), (self.width*self.rectangle_size, i)])
	
    # Fills the grid given an underlying 2D array where cells are marked 1 if a snake 
    # is present, and 0 otherwise.    
    def fillGrid(self): #This is more for testing as it is uneconomical
        for w in range(self.width+1):
            for h in range(self.height+1):
                self.clearMarker(w,h)				

    # Clears one marker from the grid
    # If you want to use this function you will need to ALSO add an update to the underlying matrix
    def clearMarker(self,x,y):
        x1 = (x-1) * self.rectangle_size
        y1 = (y-1) * self.rectangle_size
        self.canvas.create_rectangle(x1,y1, x1+self.rectangle_size, y1+self.rectangle_size, fill="white")
        self.canvas.pack()	
         
    # Places one marker on the grid
    # If you want to use this function you will need to also update the underlying matrix    
    def placeMarker(self,x,y, color):
        x1 = (x-1) * self.rectangle_size
        y1 = (y-1) * self.rectangle_size
        self.canvas.create_rectangle(x1,y1, x1+self.rectangle_size, y1+self.rectangle_size, fill=color) #"blue")
        self.canvas.pack()

    def drawNewSnake(self):
        lastSeg = self.animal.segments[len(self.animal.segments)-1]
        newSeg = self.animal.segments[0]
        self.placeMarker(lastSeg[0], lastSeg[1], self.animal.animalType.getColor())
        self.placeMarker(newSeg[0], newSeg[1], self.animal.animalType.getColor())

    def drawSnake(self):
        for segment in self.animal.segments:
            self.placeMarker(segment[0], segment[1], self.animal.animalType.getColor())
        self.placeMarker(self.food[0], self.food[1], self.animal.animalType.getFood())
