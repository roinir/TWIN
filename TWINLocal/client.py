import socket

HOST = "127.0.0.1"   # The remote host
PORT = 27015              # The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    str = input("What's your message: ")
    while str != "exit":
        s.sendall(str.encode())
        data = s.recv(1024).decode()
        print('Received', repr(data))
        str = input("What's your message: ")
    s.sendall(str.encode())
    data = s.recv(1024).decode()
    print('Received', repr(data))