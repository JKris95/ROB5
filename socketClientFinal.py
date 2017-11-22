# -*- coding: utf-8 -*-
import socket
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setup(36, GPIO.IN, pull_up_down=GPIO.PUD_UP) #Pin 36 = GPIO16

def cowGame():
    i=0
    while i==0:
        print('Ko lyd')
        time.sleep(2)
        if GPIO.input(36) == True:
            print('Ko billede')
            print('Høj ko lyd')
            s.sendall(b'C1')
            i=1
def chickenGame():
    i=0
    while i==0:
        print('Kylling lyd')
        time.sleep(2)
        if GPIO.input(36) == True:
            print('Kylling billede')
            print('Høj kylling lyd')
            s.sendall(b'C1')
            i=1
def goatGame():
    i=0
    while i==0:
        print('Gede lyd')
        time.sleep(2)
        if GPIO.input(36) == True:
            print('Gede billede')
            print('Høj gede lyd')
            s.sendall(b'C1')
            i=1
                
HOST = '192.168.137.154'    # The remote host
PORT = 50007              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
while True:
    data = s.recv(1024)
    if data == b'Cow game':
        cowGame()        
    if data == b'Chicken game':
        chickenGame()
    if data == b'Goat game':
        goatGame()

    #print(GPIO.input(36))
    #if GPIO.input(36) == True:
     #   s.sendall(b'C1')
      #  print ('Received', repr(s.recv(1024)))


