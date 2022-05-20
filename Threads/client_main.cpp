#include <iostream>

#include "client_client.h"

#define EXITO 0
#define FALLO 1

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Faltan o sobran parametros" << std::endl;
        std::cout << "Parametros esperados: <host_name> <service_name>" << std::endl;
        return FALLO;
    }
    char *host_name = argv[1];
    char *service_name = argv[2];

    Cliente cliente(host_name, service_name);
    cliente.comunicar_con_servidor();

    return EXITO;
}
