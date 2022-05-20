#include <iostream>
#include <string>

#include "client_client.h"
#include "common_socket_exceptions.h"

#define CENTINELA "fin"

Cliente::Cliente(char *host_name, char *service_name) :
    esta_cerrado(false), cliente_protocolo(host_name, service_name, &this->esta_cerrado) {}

void Cliente::comunicar_con_servidor() {
    std::string comando, argumento;

    try {
        do {
            std::cin >> comando;
            if (comando != "listar"){
                std::getline(std::cin, argumento);
            }
            cliente_protocolo.enviar_mensaje(comando, argumento);
        } while (comando != CENTINELA);
    } catch(SocketExceptions &e) {
        return;
    } catch(...) {
        std::cout << "Error desconocido" << std::endl;
    }
}
