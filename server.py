import socket


def main():
    IP = "127.0.0.1"
    PORT = 1234

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        # serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
        s.bind((IP, PORT))

        # data = s.recv(1024)
        data, _ = s.recvfrom(5)
        print(f"Received: {data.decode()}")
        # s.listen(0)
        # while True:
            
        #     print(f"Waiting for new client")
        #     clientSocket, ret = s.accept()
        #     print(f"{clientSocket=}")
        #     # print(f"Accepted connection from: {ret}")
        #     # print("Accepted connection from: ", ret)
        #     # print("Accepted connection from: {}".format(ret))

        #     while True:
        #         recvData = clientSocket.recv(1024)
        #         # print(f"Received: {recvData}")
        #         print(f"{recvData=}")
        #         clientSocket.send(recvData)

        #         if recvData.decode() == "quit":
        #             break

        # # print(f"clientSocket: {clientSocket}, ret: {ret}")


if __name__ == "__main__":
    main()