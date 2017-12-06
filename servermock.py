import socket
from random import randrange
all_connections = []
all_addresses = []
HOST=''
PORT=50007

colors = [b'red', b'green',b'blue',b'yellow',b'magenta']
animals = [b'cow',b'goat',b'giraffe',b'jimmy']
times = [b'13:00',b'14:00',b'15:00',b'17:56']



sendList = [b'False', b'False', b'False']
index = 0
numberofclients = 3
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def socket_bind(HOST,PORT,numberofclients): #setting up the socket, limitied to a fixed number of cones
    try:
        print("Binding socket to port: " + str(PORT))
        s.bind((HOST, PORT))
        s.listen(numberofclients) #setting up the socket, limitied to a fixed number of cones
    except socket.error as msg:
        print("Socket binding error: " + str(msg) +"\n" + "Retrying...")
        socket_bind()

def socket_accept(numberofclients): # accepting a fixed number of clients/cones
    for c in all_connections:
        c.close()
    del all_connections[:]
    del all_addresses[:]
    for x in range(numberofclients):
        try:
            conn, address = s.accept()
            conn.setblocking(1)
            all_connections.append(conn)
            all_addresses.append(address)
            print("\n Connection has been established:" +address[0])
            print(len(all_connections))
        except:
            print("Error accepting connections")

def chooseGame(correctCone): # lets the gamemaster chose what game catagory the questions should come from. 
    contentList = []
    pickedNumbers = []

    choice = input('Hvilket spil skal spilles?')
    if choice=='Dyre spil':
        print('Dyre spil valgt')
        for i in range(numberofclients):
            while True:
                pick = randrange(0,len(animals)) # Implement a functioning random function
                if pick not in pickedNumbers:
                    pickedNumbers.append(pick)
                    break
            contentList.append(animals[pickedNumbers[i]])


    if choice=='Farve spil':
        print('Farve spil valgt')
        for i in range(numberofclients):
            while True:
                pick = randrange(0,len(colors)) # Implement a functioning random function
                if pick not in pickedNumbers:
                    pickedNumbers.append(pick)
                    break
            contentList.append(colors[pickedNumbers[i]])


    if choice=='Ur spil':
        print('Ur spil valgt')
        for i in range(numberofclients):
            while True:
                pick = randrange(0,len(times)) # Implement a functioning random function
                if pick not in pickedNumbers:
                    pickedNumbers.append(pick)
                    break
            contentList.append(times[pickedNumbers[i]])

    contentOnCorrectCone = contentList[correctCone]
    print(contentList)
    print ("{} {}".format("\n Kør til keglen som viser:", contentOnCorrectCone))
    return contentList


def sendGameContent(contentList,cones,numberofclients):

    for i in range(numberofclients):
        cones[i].sendall(contentList[i])
    print("{} {}".format("\n Information sent to this many connections:", numberofclients))

def randomCorrect(foo): #takes the array with the default false, and assigns a random correct cone and saves that chosen correct cone.
    y = randrange(0,len(foo))
    print("{} {}".format("\n Random index chosen:", y))
    print ("{} {}".format("\n What object is at this index:", foo[y]))
    return y

def sendTrueFalse(x,y,z,numberofclients): # sends True to the correct cone and false to the rest of the cones
    print ("{} {}".format("\n Send list before adding the true cone", y))
    y[x] = b'True'
    print ("{} {}".format("\n Send list after adding the true cone", y))
    for i in range(numberofclients):
        z[i].sendall(y[i])
    print("{} {}".format("\n Information sent to this many connections:", numberofclients))

socket_bind(HOST,PORT,numberofclients)
socket_accept(numberofclients)
index = randomCorrect(all_connections) # takes the return of randomCorrect and stores it in index. 
sendTrueFalse(index, sendList, all_connections,numberofclients)
content = chooseGame(index)
sendGameContent(content,all_connections,numberofclients)