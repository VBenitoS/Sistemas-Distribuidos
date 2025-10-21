#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "Dirección no válida" << std::endl;
        return -1;
    }
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Conexión fallida al servidor" << std::endl;
        return -1;
    }
    char message[1024];
    while (true) {
        std::cout << "Ingrese un mensaje (o 'exit' para salir): ";
        std::cin.getline(message, 1024);
        send(client_fd, message, strlen(message), 0);
        if (strcmp(message, "exit") == 0) {
            break;
        }
        char buffer[1024];
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';
        std::cout << "Respuesta del servidor: " << buffer << std::endl;
    }
    close(client_fd);
    return 0;
}
