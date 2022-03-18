import dinodata
import socket
import argparse

descr = 'Runs server to allow calculation of Prey-Pred ratio'
examples = """Listens on a specified port to receive a list of pred and prey and return the pred-prey ratio"""

parser = argparse.ArgumentParser(description=descr, epilog=examples, formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument('-p', dest='port_num', type=int, default = 10000, help='Port number to listen at')
args = parser.parse_args()

port_num = args.port_num

dinos = dinodata.dinodata('')
dinofilename = 'dinosaur.dat'
dinos.readdinos(dinofilename)

s = socket.socket()
host = "localhost"
s.bind((host,port_num))

s.listen()

while True:
    
    c, addr = s.accept()
    
    while True:
        dat = c.recv(1024)
        if not dat:
            break

        dat = dat.decode('utf-8')
        dat = dat.rstrip()
        preys, preds = dat.split('|')
        preds = preds.split(',')
        preys = preys.split(',')
        num_preys, num_preds, yrrat = dinos.preypredrat(preys, preds)
        msg = f'{num_preys}\t{num_preds}\t{yrrat}'
        msg = msg.encode('utf-8')
        c.send(msg)
