class dinodata:

    def __init__(self, preys, preds):
        self.preys_list = preys
        self.preds_list = preds
        self.dinoframe = list()

    def readdinos(self, datfile):
        f = open(datfile, 'r')
        headers = f.readline().split('\t')
        errors = 0
        for line in f:
            currline = line.split('\t')
            if len(currline) == len(headers):
                self.dinoframe.append(currline)
            else:
                errors += 1
        f.close()
        return errors

    def preypredrat(self):
        import re
        num_preys = 0
        num_preds = 0
        for line in self.dinoframe:
            name = line[5]
            for animal in self.preys_list:
                preymatch = re.search(animal, name, re.IGNORECASE)
                if preymatch:
                    num_preys += 1
            for animal in self.preds_list:
                predmatch = re.search(animal, name, re.IGNORECASE)
                if predmatch:
                    num_preds += 1
        yrrat = -1
        if num_preds != 0:
            yrrat = (num_preys / num_preds)
        return (num_preys, num_preds, yrrat)
