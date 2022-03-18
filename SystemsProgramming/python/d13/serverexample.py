import socket

s = socket.socket()

host = "student00"
s.bind((host, 9997))

s.listen()

while True:

	c, addr = s.accept()

	while True:
		dat = c.recv(1024)
		if not dat:
			break

		c.send("hey hows it going".encode('utf-8'))

		dat.decode('utf-8')
		dat.rstrip()

		print(dat)

