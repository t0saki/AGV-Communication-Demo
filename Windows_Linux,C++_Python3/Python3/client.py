import _thread
from socket import *
serverName = '172.30.144.1'
#serverName = '127.0.0.1'
serverPort = 11451
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))


def rec():
    while True:
        modifiedSentence = clientSocket.recv(1024)
        print('From Server:', modifiedSentence.decode())


_thread.start_new_thread(rec, ())
while True:
    sentence = input()
    print('Send:', sentence)
    clientSocket.send(sentence.encode())

clientSocket.close()
