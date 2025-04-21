import socket


def main():
    IP = "127.0.0.1"
    PORT = 1234

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((IP, PORT))

        while True:
            toSend = input("What do you want to send? ")
            s.send(toSend.encode())
            recvString = s.recv(1024)

            print(f"Received from server: {recvString.decode()}")

            if toSend == "quit":
                break


if __name__ == "__main__":
    main()
