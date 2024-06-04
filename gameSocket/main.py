import socket

# Sunucunun IP adresi ve port numarası
SERVER_IP = "ARKADAŞIN_BILGISAYARININ_IP_ADRESI"
SERVER_PORT = 12345

# UDP soketi oluştur
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    # Kullanıcıdan giriş al
    user_input = input("Taş, kağıt, makas? ")

    # Sunucuya seçimi gönder
    sock.sendto(user_input.encode(), (SERVER_IP, SERVER_PORT))

    # Sunucudan cevap al
    data, addr = sock.recvfrom(1024)
    print(data.decode())

# Soketi kapat
sock.close()
