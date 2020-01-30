#!/usr/bin/env python3


import socket
from datetime import datetime


SERVER_HOST = ''  # Look at every interface.
SERVER_PORT = 12003  # Random low priority port.

QUEUE_SIZE = 1  # Max. requests queue size.

STRING_SIZE = 1024  # Max. string size recieved in connection messages.


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((SERVER_HOST, SERVER_PORT))  # Bind socket to host and port.
    s.listen(QUEUE_SIZE)  # Listen for a maximun of QUEUE_SIZE connection requests.

    print('[SimpleDatetimeServer/INFO] Server socket initation complete! Waiting for connection requests...')

    conn, addr = s.accept()  # Connection request is accepted, returning a tuple.
    with conn:
        print('[SimpleDatetimeServer/INFO] The address \"{}\" has established connection with the server socket!'.format(addr))
        while True:
            client_data = conn.recv(1024)  # Get data sent by client. Not necessary, we are not processing it to get the date.
            print(client_data.decode)

            current_datetime = datetime.now()  # Get current datetime.
            current_datetime_formatted = current_datetime.strftime("%d/%m/%Y - %H:%M:%S")  # Get a beautiful string.

            conn.send(str.encode(current_datetime_formatted))  # Send datetime to client.

            conn.close()  # Close connection.
