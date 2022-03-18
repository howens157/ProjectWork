#!/usr/bin/env python3

import sys
from simplecrypt import encrypt, decrypt
from base64 import b64encode, b64decode
from getpass import getpass

f = open(sys.argv[1], 'r')

for l in f:
    encoded_cipher = l.rstrip()

    cipher = b64decode(encoded_cipher)
    plaintext = decrypt(sys.argv[2], cipher).decode('utf-8')

    print(plaintext)
