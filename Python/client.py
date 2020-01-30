#!/usr/bin/env python3


import socket


SERVER_HOST = ''  # Look at every interface.
SERVER_PORT = 12003  # Random low priority port.

STRING_SIZE = 1024  # Max. string size recieved in connection messages.

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((SERVER_HOST, SERVER_PORT))  # Connect to server socket.
    s.send(b'Hi server, I am connecting.')  # Send a message to the server.

    server_data = s.recv(1024)  # Get current datetime data sent by server.

print('[SimpleDatetimeServer/INFO] Received current datetime: {}.'.format(server_data.decode()))
