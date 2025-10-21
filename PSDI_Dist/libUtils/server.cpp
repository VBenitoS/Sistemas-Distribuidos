#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

std::vector<int> clients;
std::mutex clients_mutex;

void handleClient(int client_socket, int client_id) {
    char buffer[1024];
    int bytes_read;
    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Cliente " << client_id << ": " << buffer << std::endl;
        send(client_socket, "Mensaje recibido correctamente", 30, 0);
    }
    close(client_socket);
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
    std::cout << "Cliente " << client_id << " desconectado." << std::endl;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(5000);
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error en el bind" << std::endl;
        return -1;
    }
    listen(server_fd, 5);
    std::cout << "Servidor escuchando en el puerto 5000..." << std::endl;
    int client_id = 1;
    while (true) {
        int client_socket = accept(server_fd, NULL, NULL);
        if (client_socket < 0) {
            std::cerr << "Error al aceptar la conexión" << std::endl;
            continue;
        }
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.push_back(client_socket);
        }
        std::cout << "Cliente " << client_id << " conectado." << std::endl;
        std::thread(handleClient, client_socket, client_id).detach();
        client_id++;
    }
    close(server_fd);
    return 0;
}
