#include <iostream>

#include "client_client.h"

#define FALLO 1
#define EXITO 0

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Faltan o sobran parametros" << std::endl;
        std::cout << "Parametros esperados: <host_name> <service_name> <archivo>" << std::endl;
        return FALLO;
    }
    char *host_name = argv[1];
    char *service_name = argv[2];
    char *archivo = argv[3];

    Cliente cliente(host_name, service_name, archivo);
    if (!cliente.comunicar_con_servidor()){
        return FALLO;
    }

    return EXITO;
}
