from gc import collect
import string
import collections
import sys


class NFA:
    def __init__(self, Q=None, lang=None, transitions=None, start=None, stop=None):
        # Set of states Q
        self.Q = Q
        # Alphabet
        self.lang = lang
        # Transition function
        self.transitions = transitions
        # Start state
        self.start = start
        # End state
        self.stop = stop

    def read_nfa(self, file):
        # read each line from NFA file and
        with open(file) as f:
            lines = f.readlines()
        # strip newlines from each line
        for i in range(len(lines)):
            lines[i] = lines[i].strip()

        # set start states
        self.Q = lines[0].split()

        # set alphabet
        self.lang = lines[1].split()

        # set start state
        self.start = lines[2]

        # set end state
        self.end = lines[3].split()

        # define transition functions
        self.transitions = {}
        for i in range(len(self.Q)):
            self.transitions[self.Q[i]] = {}

        for i in range(4, len(lines)):  #starts tracking from line 5 and onward
            lines[i] = lines[i].split()

            if lines[i][1] not in self.transitions[lines[i][0]]:  #if to check uniqueness of transitions
                self.transitions[lines[i][0]][lines[i][1]] = [lines[i][2]]
            else:
                self.transitions[lines[i][0]][lines[i][1]].append(lines[i][2])


    def write_nfa(self, fName):
        with open(fName, 'w') as file:
            for i in range(len(self.Q)):     # write all elements to the same line
                file.write(self.Q[i] + ' ')
            file.write('\n')
            for i in range(len(self.lang)):   # write all elements to the same line
                file.write(self.lang[i] + ' ')

            file.write('\n' + self.start + '\n')

            for i in range(len(self.end)):
                file.write(self.end[i] + ' ')
            file.write('\n')

            for keyState in self.transitions:   # nested for to write all transitions
                for keySymbol in self.transitions[keyState]:
                    for i in range(0, len(self.transitions[keyState][keySymbol])):
                        file.write(f'{keyState} {keySymbol} {self.transitions[keyState][keySymbol][i]}\n')

    def match(self, w):

        startConfig = (self.start, 0)    # tracks the state of the machine
        agenda = collections.deque()     # configurations to visit (LIFO)
        agenda.append(startConfig)
        visited = {}                    # configurations that have been checked

        finalState = False  # ultimate return value initialized to FALSE

        while agenda:  # while there are still unvisted configurations
            s = agenda.pop()
            if s[0] in self.end and s[1] == len(w): # if in accept state AND at end of submitted string
                finalState = s   # set final state to current config
                break
            if s[1] != len(w):  # if there are still symbols to read...
                if w[s[1]] in self.transitions[s[0]]:  # check transitions on next symbol
                    for node in self.transitions[s[0]][w[s[1]]]: # for each transition on next symbol...
                        if (node, s[1] + 1) not in visited: # if new node has not been visited
                            agenda.append((node, s[1] + 1))
                            visited[(node, s[1] + 1)] = (s[0], s[1], w[s[1]])

            if '&' in self.transitions[s[0]]:   # checks for epsilon transitions
                for node in self.transitions[s[0]]['&']:
                    if (node, s[1]) not in visited:
                        agenda.append((node, s[1]))
                        visited[(node, s[1])] = (s[0], s[1], '&')


        finalPath = []       #initialize finalPath list
        currentConfig = s
        finalPath.append(currentConfig)

        if finalState is not False:  # upon successful string
            print("accept")
            while currentConfig in visited:  # work backwards to reconstruct successful path
                currentConfig = visited[currentConfig][0:2]
                finalPath.append(currentConfig)

            finalPath.reverse()

            for config in finalPath[1:]:
                print(f'{visited[config][0]} {visited[config][2]} {config[0]}')
        else:                             # upon unsuccessful string
            print("reject")

        return finalState   # send currentConfig upon exit



machine = sys.argv[1]
string = sys.argv[2]

b = NFA()
b.read_nfa(machine)
state = b.match(string)
