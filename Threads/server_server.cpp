#include <iostream>

#include "server_server.h"

#define CENTINELA 'q'

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

Server::Server(char *service_name) : aceptador(service_name){}

void Server::atender_clientes(){
    char entrada = 0;
    do {
        std::cin >> entrada;
    } while (entrada != CENTINELA);

    this->aceptador.detener();
}
