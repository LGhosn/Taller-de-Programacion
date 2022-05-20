#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include "client_protocolo.h"

class  Cliente{
private:
    bool esta_cerrado;
    ClienteProtocolo cliente_protocolo;

public:
    /*
     * @brief Constructor de la clase Cliente
     * @param host_name Nombre del host
     * @param service_name Nombre del servicio
    */
    Cliente(char *host_name, char *service_name);

    /*
     * @brief Comunicación con el servidor
    */
    void comunicar_con_servidor();

    ~Cliente() = default;
};
#endif //CLIENT_CLIENT_H
