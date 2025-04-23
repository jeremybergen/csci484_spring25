import socket
import select


HEADERLENGTH = 10


def main():
    IP = "127.0.0.1"
    PORT = 1234

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((IP, PORT))

    serverSocket.listen()

    socketList = [serverSocket]
    clients = {}

    print(f"Listening for connections on {IP}:{PORT}")
    while True:
        readSockets, _, exceptionSockets = select.select(socketList, [], socketList)
        for notifiedSocket in readSockets:
            if notifiedSocket == serverSocket:
                print(f"Incoming new connection")
                clientSocket, clientAddress = notifiedSocket.accept()
                print(f"{clientAddress}: Connected")
                msgHeader = clientSocket.recv(HEADERLENGTH)
                msgHeader = int(msgHeader.decode().strip())
                username = clientSocket.recv(msgHeader)
                socketList.append(clientSocket)
                clients[clientSocket] = username.decode()
            else:
                message = notifiedSocket.recv(1024)
                print(f"Received: {message.decode()}")
                user = clients[notifiedSocket]
                for clientSocket in clients:
                    if clientSocket != notifiedSocket:
                        clientSocket.send(f"{len(user):<{HEADERLENGTH}}{user}".encode())
                        print(f"{len(user):<{HEADERLENGTH}}{user}".encode())
                        clientSocket.send(message)
                        print(f"{message}")

    serverSocket.close()
    print(f"{f"{"continue"}"}")


if __name__ == "__main__":
    main()