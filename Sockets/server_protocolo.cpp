#include "server_protocolo.h"
#include <arpa/inet.h>

#define FALLO 1
#define EXITO 0
#define TAMANIO_UINT8 1
#define TAMANIO_UINT16 2

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/
void ServerProtocolo::enviar_colisiones(std::vector< std::tuple<int, int> > colisiones) {
    for (auto colision : colisiones){
        uint16_t colision_x, colision_y;
        std::tie(colision_x, colision_y) = colision;

        uint16_t colision_x_net = htons(colision_x);
        uint16_t colision_y_net = htons(colision_y);
        this->cliente.sendall(&colision_x_net, TAMANIO_UINT16, this->was_closed);
        this->cliente.sendall(&colision_y_net, TAMANIO_UINT16, this->was_closed);
    }
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/
ServerProtocolo::ServerProtocolo(char *service_name, bool *was_closed) : 
    server(service_name), cliente(this->server.accept()), was_closed(was_closed) {}

int ServerProtocolo::recibir_comando(uint8_t *edificio, uint16_t *x, uint16_t *y){
    this->cliente.recvall(edificio, TAMANIO_UINT8, this->was_closed);

    this->cliente.recvall(x, TAMANIO_UINT16, this->was_closed);
    *x = ntohs(*x);

    this->cliente.recvall(y, TAMANIO_UINT16, this->was_closed);
    *y = ntohs(*y);
    return EXITO;
}

int ServerProtocolo::notificar_error(std::vector< std::tuple<int, int> > colisiones){
    uint8_t error = 1;
    uint8_t cantidad_colisiones = (uint8_t)colisiones.size();
    this->cliente.sendall(&error, TAMANIO_UINT8, this->was_closed);
    this->cliente.sendall(&cantidad_colisiones, TAMANIO_UINT8, this->was_closed);

    enviar_colisiones(colisiones);
    return EXITO;
}

int ServerProtocolo::notificar_ok(){
    uint8_t ok = 0;
    this->cliente.sendall(&ok, TAMANIO_UINT8, this->was_closed);
    return EXITO;
}
