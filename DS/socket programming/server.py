import socket
import threading

def handle(client):
    # Handle each client connection
    while True:
        try:
            # Receive data in chunks of 1024 bytes
            data = client.recv(1024)
            if data:
                print("Received data from client")
                client.send(data)  # Echo back the received data
            else:
                break  # No data means the client disconnected
        except Exception as e:
            print(f"Error: {e}")
            break

    client.close()

def start_server(host="127.0.0.1", port=4000):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)
    print(f"Server listening on port {port}...")

    while True:
        try:
            client, address = server.accept()  # Accept client connection
            print(f"Connected to {address}")
            # Handle client connection in a new thread
            thread = threading.Thread(target=handle, args=(client,))
            thread.start()
        except Exception as e:
            print(f"Error: {e}")
            break

    server.close()

start_server()
