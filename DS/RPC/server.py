import socket
import threading


def operation(data):
    l = data.split()
    
    if(l[1] == '+'):
        return int(l[0]) + int(l[2])
    else:
        return int(l[0]) * int(l[2])

def handle(client):

    while True:

        try:
            data = client.recv(1024).decode("utf-8")
            print(data)
            ans = operation(data)
            print(ans)
            client.send(str(ans).encode("utf-8"))
        except Exception as e:
            print(e)
            break
    client.close()

def start_server(host = "127.0.0.1",port = 5000):
    host = socket.gethostname()
    server = socket.socket()

    server.bind((host,port))

    server.listen(5)

    while True:
        
        try:
            client ,add = server.accept()

            thread = threading.Thread(target=handle,args=(client,))
            thread.start()
        except Exception as e:
            print(e)
            break 
    server.close()

start_server()