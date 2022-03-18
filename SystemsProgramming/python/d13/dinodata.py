class dinodata:
    import pdb
    def __init__(self, en_pw):
        self.dinoframe = list()
        self.en_pw = en_pw

    def readdinos(self, datfile):
        f = open(datfile, 'r')
        headers = f.readline().split('\t')
        self.dinoframe.append(headers)
        errors = 0
        for line in f:
            currline = line.split('\t')
            if len(currline) == len(headers):
                self.dinoframe.append(currline)
            else:
                errors += 1
        f.close()
        return errors

    def preypredrat(self, preys, preds):
        import re
        self.preys_list = preys
        self.preds_list = preds
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

    def dinoencrypt(fcn):
        from simplecrypt import encrypt, decrypt
        from base64 import b64encode, b64decode
        def inner(self, datfile, dat):
            if self.en_pw == '':
                fcn(self, datfile, dat)
            else:
                edat = encrypt(self.en_pw, dat)
                edat = b64encode(edat).decode('utf-8')
                fcn(self, datfile, edat)
        return inner

    @dinoencrypt
    def filewriteline(self, datfile, dat):
        fd = open(datfile, 'a')
        fd.write(dat)
        fd.write('\n')
        fd.close
    
    def save_df(self, datfile, cols, num_print):
        import pdb
        for i in range(0, num_print+1):
            dat = ''
            #pdb.set_trace()
            for j in cols:
                dat = dat + '\t' + self.dinoframe[i][j]
            dat = dat.lstrip()
            self.filewriteline(datfile, dat)
            
        
