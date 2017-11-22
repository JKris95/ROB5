import socket
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(36, GPIO.IN, pull_up_down=GPIO.PUD_UP) #Pin 36 = GPIO16


HOST = '192.168.1.135'    # The remote host
PORT = 50007              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
#s.sendall(b'ready')
while True:
    #if data == 'cow game':
     #   print('Jeg er en ko')
      #  data = 0
    print(GPIO.input(36))
    if GPIO.input(36) == True:
        print('hej')
        data = s.recv(1024)
        s.sendall(b'C1')
        print ('Received', repr(data))


