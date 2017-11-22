import socket
def gameChose():
        if nb=='Cow game':
            print('cow game')
            conn.sendall(b'Cow game')
        if nb=='Chicken game':
            conn.sendall(b'Chicken game')
        if nb=='Goat game':
            print('Goat game')
            conn.sendall(b'Goat game')
    
Cone = b'C1'
Ready = b'ready'
HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
print ('Connected by', addr)
while 1:
    nb = input('What kind of game would you like to play?')
    gameChose()
    while nb !='Cow game' and nb !='Chicken game' and nb !='Goat game':
        nb = input('Wrong game, plz type: Cow game, Chicken game or Goat game')
        gameChose()
    while conn.recv(1024) != b'C1':
        print('Cone 1 got hit')

