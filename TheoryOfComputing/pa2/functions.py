import string
import sys
import copy
import collections
validChars = string.printable

# node class for regular expression parse tree
class node:
    def __init__(self, nodeType=None, args=None):
        self.nodeType = nodeType
        self.args = args

class NFA:
    def __init__(self, Q=[], lang=[], transitions={}, start=None, end=[]):
        # Set of states Q
        self.Q = Q
        # Alphabet
        self.lang = lang
        # Transition function
        self.transitions = transitions
        # Start state
        self.start = start
        # End state
        self.end = end

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
            # print("accept")
            # while currentConfig in visited:  # work backwards to reconstruct successful path
            #     currentConfig = visited[currentConfig][0:2]
            #     finalPath.append(currentConfig)

            # finalPath.reverse()

            # for config in finalPath[1:]:
            #     print(f'{visited[config][0]} {visited[config][2]} {config[0]}')
            return True
        else:                             # upon unsuccessful string
            #print("reject")
            return False

        #return finalState   # send currentConfig upon exit
    
    def set_start(self, start_state):
        self.start = start_state
    
    def add_state(self, new_state):
        self.Q.append(new_state)
    
    def add_transition(self, add_key, add_symbol, add_value):
            if add_symbol not in self.transitions[add_key]:  #if to check uniqueness of transitions
                self.transitions[add_key][add_symbol] = [add_value]
            else:
                self.transitions[add_key][add_symbol].append(add_value)
    
    def add_end_state(self, end_state):
        self.end.append(end_state)

    def add_alphabet(self, new_characters):
        if new_characters not in self.lang:
            self.lang.append(new_characters)

    #print the nfa to stdout instead of writing to a file
    def print_nfa(self):
        for i in range(len(self.Q)):     # write all elements to the same line
            sys.stdout.write(self.Q[i] + ' ')
        sys.stdout.write('\n')
        for i in range(len(self.lang)):   # write all elements to the same line
            sys.stdout.write(self.lang[i] + ' ')

        sys.stdout.write('\n' + self.start + '\n')

        for i in range(len(self.end)):
            sys.stdout.write(self.end[i] + ' ')
        sys.stdout.write('\n')

        for keyState in self.transitions:   # nested for to write all transitions
            for keySymbol in self.transitions[keyState]:
                for i in range(0, len(self.transitions[keyState][keySymbol])):
                    sys.stdout.write(f'{keyState} {keySymbol} {self.transitions[keyState][keySymbol][i]}\n')        

# return a new NFA that has the language of the union of the languages of m1 and m2
def union_nfa(m1, m2):
    m3 = copy.deepcopy(m1)

    numExclams = 0
    # we need to check if m1 already had states with exclamation points to avoid naming multiple states the same thing.
    # If it does, increment the number of exclamation points and then check again
    keepGoing = True
    while keepGoing:
        keepGoing = False
        for state2 in m2.Q:
            newState2 = state2 + '!'*numExclams 
            if newState2 in m3.Q:
                numExclams += 1
                keepGoing = True
                break

    # Now that we know how many exclamation points we need to add to m2's
    stateNameMod = '!'*numExclams

    # Add the old states and transitions from m2 but with new names
    for state in m2.Q:
        m3.add_state(f"{state}{stateNameMod}")
        m3.transitions[f"{state}{stateNameMod}"] = {}
        for key, value in m2.transitions[state].items():
            for val in value:
                m3.add_transition(f"{state}{stateNameMod}", key, f"{val}{stateNameMod}")

    # Add the end states of m2 and new end states
    for state in m2.end:
        m3.add_end_state(f"{state}{stateNameMod}")

    # Create a new start state and check that its name is valid
    newStartState = f'qstart{stateNameMod}'
    while True:
        if newStartState in m3.Q:
            newStartState += '!'
        else:
            break
    # add the new start state and add epsilon transitions from it to each of the old start states
    m3.add_state(newStartState)
    m3.set_start(newStartState)
    m3.transitions[newStartState] = {}
    m3.add_transition(newStartState, '&', m1.start)
    m3.add_transition(newStartState, '&', f'{m2.start}{stateNameMod}')

    for letter in m2.lang:
        m3.add_alphabet(letter)
    
    return m3

def star_nfa(m1):
    m3 = copy.deepcopy(m1)

    numExclams = 0
    # we need to check if m1 already had states with exclamation points to avoid naming multiple states the same thing.
    # If it does, increment the number of exclamation points and then check again
    keepGoing = True
    while keepGoing:
        keepGoing = False
        for state in m3.Q:
            newState = state + '!'*numExclams 
            if newState in m3.Q:
                numExclams += 1
                keepGoing = True
                break

    # Now that we know how many exclamation points we need to add to m2's
    stateNameMod = '!'*numExclams

    # Add a new start state with an epsilon transition to the old start state
    newStartState = f'qstart{stateNameMod}'
    m3.add_state(newStartState)
    m3.set_start(newStartState)
    m3.transitions[newStartState] = {}
    m3.add_transition(newStartState, '&', m1.start)
    m3.add_end_state(newStartState)

    # add epsilon transitions from all of the end states to the old start state
    for state in m1.end:
        m3.add_transition(state, '&', m1.start)
    
    return m3

#recursive parser for regular expressions, returns a root node for a parse tree for the
#regular expression
def parse(w):
    if len(w) == 0:
        return node('epsilon', [])
    x, i = parseExpr(w, 0)
    if i == len(w):
        return x
    else:
        print(i)
        print('parseError')
        exit(1)

def parseExpr(w,i):
    if w[i] == '|' or w[i] == ')':
        args = []
        args.append(node('epsilon', []))
    else:
        x, i = parseTerm(w, i)
        args = [x]
    while i < len(w) and w[i] == '|':
        if i+1 >= len(w):
            args.append(node('epsilon', []))
            i += 1
        elif w[i+1] == ')':
            args.append(node('epsilon', []))
            i += 1
        elif w[i+1] == '|':
            args.append(node('epsilon', []))
            i += 1
        else:
            x, i = parseTerm(w, i+1)
            args.append(x)
    return node('union', args), i

def parseTerm(w,i):
    x, i = parseFactor(w, i)
    args = [x]
    if i < len(w):
        while w[i] != '|' and w[i] != ')':
            x, i = parseFactor(w, i)
            args.append(x)
            if i >= len(w):
                break
    return node('concat', args), i

def parseFactor(w,i):
    x, i = parsePrimary(w, i)
    args = [x]
    if i < len(w) and w[i] == '*':
        return node('star', args), i+1
    return x, i

def parsePrimary(w,i):
    if w[i] == '(':
        x, i = parseExpr(w, i+1)
        return node('group', [x]), i+1
    elif w[i] in validChars:
        return node('symbol', w[i]), i+1

# Print the parse tree in a Scheme format
def nodeTraversal(n, w=''):
    if (n.nodeType == 'union' and len(n.args) < 2) or (n.nodeType == 'concat' and len(n.args) < 2):
        pass
    else:
        if n.nodeType != 'epsilon':
            w += f'({n.nodeType} '
        else:
            w += f'({n.nodeType}'
    if n.nodeType == 'symbol':
        w += f'"{n.args}")'
        return w
    
    for index in range(len(n.args)):
        w = nodeTraversal(n.args[index], w)
        if index < len(n.args)-1:
            w += ' '
    #simplify the union or concatenation of a single argument
    if (n.nodeType == 'union' and len(n.args) < 2) or (n.nodeType == 'concat' and len(n.args) < 2):
        pass
    else:
        w += f')'
    
    return w

# return a new NFA created that accepts the union of the languages represented by m1 and m2
def concat_nfa(m1, m2):
    m3 = copy.deepcopy(m1)

    numExclams = 0
    # we need to check if m1 already had states with exclamation points to avoid naming multiple states the same thing.
    # If it does, increment the number of exclamation points and then check again
    keepGoing = True
    while keepGoing:
        keepGoing = False
        for state2 in m2.Q:
            newState2 = state2 + '!'*numExclams 
            if newState2 in m3.Q:
                numExclams += 1
                keepGoing = True
                break

    # Now that we know how many exclamation points we need to add to m2's
    stateNameMod = '!'*numExclams

    #add all old states and transitions from m2 with new names
    for state in m2.Q:
        m3.add_state(f"{state}{stateNameMod}")
        m3.transitions[f"{state}{stateNameMod}"] = {}
        for key, value in m2.transitions[state].items():
            for val in value:
                m3.add_transition(f"{state}{stateNameMod}", key, f"{val}{stateNameMod}")

    # clear the old accept states
    m3.end = []

    # add m2's accept states as accept states
    for state in m2.end:
        m3.add_end_state(f"{state}{stateNameMod}")

    # add transitions from m1's accept states to m2's start state
    for state in m1.end:
        m3.add_transition(state, '&', f"{m2.start}{stateNameMod}")

    #combine the alphabets
    for letter in m2.lang:
        m3.add_alphabet(letter)
    
    return m3

def string_nfa(w):
    my_nfa = NFA()
    my_nfa.Q = []
    my_nfa.lang = []
    my_nfa.transitions = {}
    my_nfa.start = None
    my_nfa.end = []
    # create states
    for index in range(len(w)+1):
        my_nfa.add_state(f'q{index}')

    for i in range(len(my_nfa.Q)):
        my_nfa.transitions[my_nfa.Q[i]] = {}
    # set start state
    my_nfa.set_start('q0')

    # add transitions and create alphabet
    for index in range(0, len(w)):
        my_nfa.add_transition(f'q{index}', w[index], f'q{index+1}')
        my_nfa.add_alphabet(w[index])

    # set end state
    my_nfa.add_end_state(f'q{len(w)}')

    return my_nfa

def re_to_nfa(re):
    #parse the re
    top = parse(re)
    #create an NFA from the parse tree
    m = createNFA(top)
    return m

#createNFA is a recursive function that creates an NFA from a parse tree by recursively calling createNFA
#on currNode's children nodes until it reaches a symbol that an NFA can be created from and then performing
#the correct construction operation on the children NFAs
def createNFA(currNode):
    #if nodeType is symbol, we can use string_nfa to create an NFA to match that symbol
    if currNode.nodeType == 'symbol':
        return string_nfa(currNode.args)
    #if nodeType is epsilon, we can use string_nfa to create an NFA to match epsilon
    elif currNode.nodeType == 'epsilon':
        return string_nfa("")
    #if nodeType is group, just call createNFA on the child of that group
    elif currNode.nodeType == 'group':
        return createNFA(currNode.args[0])
    #if nodeType is star, call createNFA on the child of the star and then perform the star construction on the result
    elif currNode.nodeType == 'star':
        return star_nfa(createNFA(currNode.args[0]))
    #if nodeType is union, call createNFA on all children of the node and then create an NFA of the union of all those children, return that NFA
    elif currNode.nodeType == 'union':
        numChildren = len(currNode.args)
        if numChildren == 1:
            return createNFA(currNode.args[0])
        else:
            childNFAs = []
            for child in currNode.args:
                childNFAs.append(createNFA(child))
            tempNFA = union_nfa(childNFAs[0], childNFAs[1])
            for i in range(2, len(childNFAs)):
                tempNFA = union_nfa(tempNFA, childNFAs[i])
            return tempNFA
    #if nodeType is concat, call createNFA on all children of the node and then create an NFA of the concatenation of all those children, return that NFA
    elif currNode.nodeType == 'concat':
        numChildren = len(currNode.args)
        if numChildren == 1:
            return createNFA(currNode.args[0])
        else:
            childNFAs = []
            for child in currNode.args:
                childNFAs.append(createNFA(child))
            tempNFA = concat_nfa(childNFAs[0], childNFAs[1])
            for i in range(2, len(childNFAs)):
                tempNFA = concat_nfa(tempNFA, childNFAs[i])
            return tempNFA
    else:
        print("nodeTypeError")
        exit(1)