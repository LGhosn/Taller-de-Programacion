#include <iostream>

#include "server_server.h"

#define EXITO 0
#define FALLO 1

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Faltan o sobran parametros" << std::endl;
        std::cout << "Parametros esperados: <service_name>" << std::endl;
        return FALLO;
    }
    char *service_name = argv[1];

    Server server(service_name);
    server.atender_clientes();

    return EXITO;
}
