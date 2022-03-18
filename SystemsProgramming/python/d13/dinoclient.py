import socket
import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-p', dest='port', type=int, default=9999, help='port number for connection')
parser.add_argument('-n', dest='hostname', type=str, default='localhost', help='host number for connection')
parser.add_argument('-r', dest='preds', action='append', required=True, help='single predator animal')
parser.add_argument('-y', dest='preys', action='append', required=True, help='single prey animal')
args = parser.parse_args()

s = socket.socket()
s.settimeout(60)
s.connect((args.hostname, args.port))

preys = ','.join(args.preys)
preds = ','.join(args.preds)
msg = f'{preys}|{preds}\n'

msg = msg.encode('utf-8')

s.send(msg)

ret = s.recv(128)
ret = ret.decode('utf-8')

print(ret)
