import socket

s = socket.socket()

s.connect(("student02.cse.nd.edu", 22))

mesg = s.recv(128)

mesg = mesg.decode('utf-8')

print(mesg)

tosend = "ERROR"

s.send(tosend.encode('utf-8'))

s.close()

# other functions/resources to keep in mind:
#  socket.settimeout()
#  ConnectionRefusedError
#  socket.timeout

# https://docs.python.org/3/library/socket.html

