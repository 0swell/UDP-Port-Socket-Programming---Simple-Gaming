#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 12345

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server_addr, client_addr;
    int len = sizeof(client_addr), n;
    char buffer[1024];

    // Winsock başlat
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // UDP soketi oluştur
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d\n", WSAGetLastError());
        return 1;
    }

    // Sunucu adresi ve port numarası
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Soketi bağla
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    srand((unsigned int)time(NULL));  // Rastgele tohumlama sadece bir kez yapılır

    while (1) {
        // Kullanıcının seçimini al
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &len);
        buffer[n] = '\0';

        // Rastgele seçim yap
        int random_num = rand() % 3;

        // Kullanıcının seçimine göre kazananı belirle
        const char* choices[3] = { "Tas", "Kagit", "Makas" };
        char result[1024];
        if (strcmp(buffer, choices[random_num]) == 0) {
            snprintf(result, sizeof(result), "Berabere! Sunucunun secimi: %s", choices[random_num]);
        }
        else if ((strcmp(buffer, "Tas") == 0 && strcmp(choices[random_num], "Makas") == 0) ||
            (strcmp(buffer, "Kagit") == 0 && strcmp(choices[random_num], "Tas") == 0) ||
            (strcmp(buffer, "Makas") == 0 && strcmp(choices[random_num], "Kagit") == 0)) {
            snprintf(result, sizeof(result), "Kazandiniz! Sunucunun secimi: %s", choices[random_num]);
        }
        else {
            snprintf(result, sizeof(result), "Kaybettiniz! Sunucunun secimi: %s", choices[random_num]);
        }

        // Sonucu gönder
        sendto(sockfd, result, strlen(result), 0, (struct sockaddr*)&client_addr, len);
    }

    // Soketi kapat
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
