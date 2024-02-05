import socket
import time

def send_chunked_message(sock, message):
    chunk_size = 5
    for i in range(0, len(message), chunk_size):
        sock.send(message[i:i+chunk_size].encode())
        time.sleep(1)  # Simulate network delay

def main():
    server_address = ('127.0.0.1', 5151)  # Update with your server's IP and port
    message = "Hello World!\n"

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect(server_address)
        send_chunked_message(sock, message)

if __name__ == "__main__":
    main()
