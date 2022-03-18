Hayden Owens
Programming Paradigms
Assignment 3 - Report

i: 
    I completed this assignment on my own, so all contributions are mine.

ii: 
    I represented the board and the rules of the game using 3 separate classes: Board,
    Guess, and Letter. 

    A Letter has members holding the value or actual letter being represented, the 
    location or index of the letter in the larger word that it is a part of, and the 
    state of the Letter (0 for no state, 1 for correct, 2 for included but wrong 
    position, and 3 for not included). It has a set() method to just set the value
    to a new letter. It also has a checkLetter(wordToCheck) method which checks the 
    Letter against wordToCheck (which will be the answer) to set the state of the Letter
    accordingly.

    A Guess has members to hold the length of the guess, an array of Letter objects with
    a corresponding length, and an index for the current location that is being written
    to in the Guess. For example, if the guess currently is ar---, currLocation will be
    2. Guess also has a check method(wordToCheck) which checks that the current guess is
    valid (complete word, in the word list). It also will alert the user if the guess is
    not valid. If the guess is valid, it then valls checkLetter(wordToCheck) for each
    Letter it holds in order to set the states of all of its Letters. It also has a
    checkWin() method which is called after the user submits a valid guess which checks
    to see if all the letters are in state 1. If so the user has won. Finally, it has
    addLetter() and backspace() methods which are used to add or take way letters from
    the Guess.

    Finally, a Board has members holding the answer the user is trying to guess, the 
    number of guesses the user gets, the length of each guess, and the guess number that 
    the user is currently on. It also has a member that is an array of numGuesses Guess 
    objects. Board has 3 methods. First, addLetter() and backspace() which just calls 
    the addLetter() or backspace() method of the Guess that the user is currently 
    working on. It also has a checkGuess() method which first calls the Guess check()
    method on the current Guess, then if that was a valid Guess, increments numGuesses
    to move on from the submitted Guess. Then finally, it calls the Guess method 
    checkWin() to see if the user has won by submitting that Guess. If so, the game ends
    and the user is alerted that they have won. If not, it checks if the user has used
    numGuesses already. If so, the game ends and the user is alerted that they have won.
    
    I felt that this breakdown of classes was very intuitive. A game board has rules 
    and consists of 6 guesses. Each guess has rules and consists of 5 letters. And each
    letter is colored according to a set of rules and consists of a value and a state.
    It also allowed me to handle all the rules of the game within my class structure 
    which allows my code to be easily divided into two sections with the first section
    handling the rules of the game, and the second section handling user interaction by
    drawing to the board and checking for mouseclicks. It also made my code much more 
    modular. I could create an alternate version of Wordle with more guesses or longer 
    words with the exact same classes.

iii:
    I thought this was fairly easy to accomplish in JavaScript. Classes are easy to 
    define and instantiate and it is also very easy to draw to the screen and set up
    event listeners for user input. I think this makes JavaScript ideal for creating
    a web-based application like Wordle.
    
iv:
    My Wordle:
    I implemented a fairly standard version of Wordle due to the fact that I worked on
    this individually. I did implement the backspace function as well as displaying
    error messages to the user if they try to submit an invalid guess. One aspect of 
    note is that for my implementatiion, if the words only has one 'a' which has 
    already been found, and a is guessed in another location, it will still be marked 
    yellow for being in the word but not in that spot. This differs from how the real 
    Wordle works, but I think this rule set is a bit more consistent in how it labels 
    yellow letters. It also is a bit easier to implement with my class structure.
