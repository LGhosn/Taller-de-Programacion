#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "server_protocolo.h"
#include "server_partida.h"
#include "server_manejador.h"
#include "server_aceptador.h"

class Server{
private:
    Aceptador aceptador;

public:
    explicit Server(char *service_name);

    void atender_clientes();

    ~Server() = default;
};
#endif //SERVER_SERVER_H
