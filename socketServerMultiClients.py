import socket
import sys
import threading
import time
from queue import Queue

NUMBER_OF_THREADS = 2
JOB_NUMBER = [1, 2]
queue = Queue()
all_connections = []
all_addresses = []

def socket_create():
        try:
            global HOST
            global PORT
            global s
            HOST=''
            PORT=50007
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except socket.error as msg:
            print("Socket creation error: " + str(msg))
            
def socket_bind():
    try:
        global HOST
        global PORT
        global s
        print("Binding socket to port: " + str(PORT))
        s.bind((HOST, PORT))
        s.listen(3)
    except socket.error as msg:
        print("Socket binding error: " + str(msg) +"\n" + "Retrying...")
        socket_bind()

def socket_accept():
    for c in all_connections:
        c.close()
    del all_connections[:]
    del all_addresses[:]
    while 1:
        try:
            conn, address = s.accept()
            conn.setblocking(1)
            all_connections.append(conn)
            all_addresses.append(address)
            print("\n Connection has been established:" +address[0])
            for conn in all_connections:
                conn.sendall(b'Cow game')
        except:
            print("Error accepting connections")
    
def chose_game():
    while 1:
        nb = input('What kind of game would you like to play?')
        send_recive(nb)
        while nb !='Cow game' and nb !='Chicken game' and nb !='Goat game':
            nb = input('Wrong game, plz type: Cow game, Chicken game or Goat game')
            send_recive(nb)
        while conn.recv(1024) != b'C1':
            print('Cone 1 got hit')

def send_recive(nb):
        if nb=='Cow game':
            conn.sendall(b'Cow game')
        if nb=='Chicken game':
            conn.sendall(b'Chicken game')
        if nb=='Goat game':
            conn.sendall(b'Goat game')

def create_worker():
    for _ in range(NUMBER_OF_THREADS):
        t = threading.Thread(target=work)
        t.deamon = True
        t.start()

def work():
    while True:
        x=queue.get()
        if x == 1:
            socket_create()
            socket_bind()
            socket_accept()
        if x == 2:
            chose_game()
        queue.task_done()
            
def create_jobs():
    for x in JOB_NUMBER:
        queue.put(x)
    queue.join()

if __name__ == "__main__":
    create_worker()
    create_jobs()

            
