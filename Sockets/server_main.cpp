#include <iostream>

#include "server_server.h"

#define FALLO 1
#define EXITO 0

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Faltan o sobran parametros" << std::endl;
        std::cout << "Parametros esperados: <service_name> <ancho> <alto>" << std::endl;
        return FALLO;
    }
    char *service_name = argv[1];
    int ancho, alto;
    ancho = atoi(argv[2]);
    alto = atoi(argv[3]);

    Server server(service_name, ancho, alto);
    if (!server.comunicar_con_cliente()) {
        return FALLO;
    }

    return EXITO;
}


