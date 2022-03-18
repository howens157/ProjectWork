import argparse
import hashlib
import exrex
import ray

ray.init()

descr="This program will attempt to crack a given encrypted password using brute force given a regular expression to check against the encrypted password"

parser = argparse.ArgumentParser(description=descr, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-r', dest='usr_regex', type=str, help='The regex to check against the encrypted passsword.', required=True)
parser.add_argument('-t', dest='numthreads', type=int, help='The number of threads to be used when parallelizing the program.', default=1)
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument('-f', dest='PWF', type=str, default='', help='Specifies a file to read a group of encrypted passwords from. The regex will be checked against each of them.')
group.add_argument('-e', dest='EPW', type=str, default='', help='An encrypted password passed through the command line. The regex will be checked against this.')
group.add_argument('-p', dest='PW', type=str, default='', help='A cleartext password passed through the command line. This will be encrypted and then the regex will be checked against it for debugging purposes.')

args = parser.parse_args()
usr_regex = args.usr_regex
numthreads = args.numthreads
if(numthreads > 999):
    numthreads = 1
    print("numthreads is too large, resetting to 1")
PWF = args.PWF
EPW = args.EPW
PW = args.PW

@ray.remote
def cryptandtest(candidate, encrypted):
    candidate_enc = candidate.encode('utf-8') 
    candidate_enc_obj = hashlib.md5(candidate_enc)
    candidate_hex = candidate_enc_obj.hexdigest()
    if(candidate_hex == encrypted):
        return True
    else:
        return False

encryptedlist = list()
if(PWF != ""):
    f = open(PWF, 'r')
    numpasswords = 0
    for line in f:
        encryptedlist.append(line.strip())
        numpasswords = numpasswords + 1
elif(EPW != ""):
    encryptedlist.append(EPW)
    numpasswords = 1
elif(PW != ""):
    input_enc = PW.encode('utf-8')
    input_enc_obj = hashlib.md5(input_enc)
    encryptedlist.append(input_enc_obj.hexdigest())
    numpasswords = 1
    

gen = exrex.generate(usr_regex)
keepgen = True
while encryptedlist and keepgen:
    currregex = list()
    for i in range(0, numthreads):
        try:
            currregex.append(next(gen))
        except StopIteration:
            keepgen = False

    for currpass in encryptedlist:
        ray_objs = list()
        for ex in currregex:
            ray_objs.append(cryptandtest.remote(ex, currpass))
        results = ray.get(ray_objs)
        result_index = 0
        for currresult in results:
            if(currresult):
                encryptedlist.remove(currpass)
                print(f'{currpass} decrypted into {currregex[result_index]}')
            result_index = result_index + 1
