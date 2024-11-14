
import socket

def start_client(host = "127.0.0.1",port = 5000):
    host = socket.gethostname()

    client  = socket.socket()

    client.connect((host,port))

    while True:
        n1 = input("enter the number")
        n2 = input("enter the number")

        client.send((n1 +" + "+ n2).encode("utf-8"))

        data = client.recv(1024).decode("utf-8")
        print(data)

start_client()


