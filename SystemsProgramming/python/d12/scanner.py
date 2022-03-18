import socket
import sys

filename = sys.argv[1]

f = open(filename, 'r')

for line in f:
    (host, port) = line.split(':')
    port = int(port)
    s = socket.socket()
    s.settimeout(2)
    try:
        s.connect((host, port))
        mesg = s.recv(128)
        mesg = mesg.decode('utf-8')
    except ConnectionRefusedError as ex:
        mesg = '<connection refused>'
    except socket.timeout as ex:
        mesg = '<connection timeout>'
    print(f'{line.strip():<30s}{mesg.strip()}')
    s.close()
