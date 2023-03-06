# https://stackoverflow.com/questions/50852062/send-byte-over-tcp-python

import socket
import struct
localIP = ""
localPort = 4558
bufferSize = 1024
msg = b'0x9f88070000820282020282028201018202820101820018281a000f424085010100005823526561647920746f2067656e657261746520612033322d62797465207061796c6f6164ff'
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((localIP, localPort))
s.send(msg)
data = s.recv(bufferSize)
s.close()
print( "received data:", data)
