import socket
import pathlib 


def send_and_recive(file1,file2):

    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect(("127.0.0.1",4000))

    sendFile = pathlib.Path(file1)
    revFile = pathlib.Path(file2)

    with sendFile.open("rb") as file:

        while(chunk := file.read(1024)):
            client.sendall(chunk)

    client.shutdown(socket.SHUT_WR)

    with revFile.open("wb") as file:

        while True:
            chunk = client.recv(1024)
            if not chunk:
                
                break
            
            file.write(chunk)
            print("revived chunk from server",chunk)

    client.close()

send_and_recive(r"C:\Users\omshi\Desktop\LP1\DS\socket programming\sample.txt",r"C:\Users\omshi\Desktop\LP1\DS\socket programming\echo_sample.txt")

