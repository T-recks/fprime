import socket

count = 0
# localIP     = "127.0.0.1"
# localIP     = "10.105.86.160"
localIP     = ""
localPort   = 4556
# localPort   = 4558
bufferSize  = 1024

msgFromServer       = "Hello TCP Client"
bytesToSend         = str.encode(msgFromServer)

# Create a datagram socket
s = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)

# avoid Errno 98
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind to address and ip
s.bind((localIP, localPort))
s.listen()
print("TCP server up and listening")

# Listen for incoming connections
while(True):
    conn, addr = s.accept()
    try:
        message = conn.recv(bufferSize)

        if message:
            count += 1
            # clientMsg = "message: {}".format(message)
            clientMsg = "{}: {}".format(count, message)
            print(clientMsg)
    finally:
        conn.close()

    # Sending a reply to client
    # UDPServerSocket.sendto(bytesToSend, address)
