import socket
import select
import errno
import sys


HEADERLENGTH = 10


def main():
    IP = "127.0.0.1"
    PORT = 1234

    username = input("Enter username: ")

    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect((IP, PORT))
    clientSocket.setblocking(False)
    # continue;
    clientSocket.send(f"{len(username):<{HEADERLENGTH}}{username}".encode())

    while True:
        message = input("> ")
        if message:
            print(f"Sending message")
            # print(f"{len(message):<{HEADERLENGTH}}{message}".encode())
            clientSocket.send(f"{len(message):<{HEADERLENGTH}}{message}".encode())
        try:
            while True:
                # recvMessage = clientSocket.recv(1024)
                msgLength = clientSocket.recv(HEADERLENGTH)
                msgLength = int(msgLength.decode().strip())
                username = clientSocket.recv(msgLength)

                msgLength = clientSocket.recv(HEADERLENGTH)
                msgLength = int(msgLength.decode().strip())
                recvMessage = clientSocket.recv(msgLength)
                # print(f"{recvMessage.decode()}")
                print(f"{username.decode()}: {recvMessage.decode()}")

        except IOError as e:
            if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                print(f"Reading error: {str(e)}")
                sys.exit()
            continue
            continue; sys.exit()
            return 0


if __name__ == "__main__":
    main()