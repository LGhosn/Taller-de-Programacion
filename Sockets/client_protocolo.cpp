#include "client_protocolo.h"
#include <iostream>
#include <arpa/inet.h>

#define FALLO 1
#define EXITO 0
#define TAMANIO_UINT8 1
#define TAMANIO_UINT16 2

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/
ClientProtocolo::ClientProtocolo(char *host_name, char *service_name, bool *was_closed) : 
    cliente(host_name, service_name), was_closed(was_closed) {}

int ClientProtocolo::enviar_comando(uint8_t edificio, uint16_t x, uint16_t y){
    uint16_t x_net = htons(x);
    uint16_t y_net = htons(y);
    this->cliente.sendall(&edificio, TAMANIO_UINT8, this->was_closed);
    this->cliente.sendall(&x_net, TAMANIO_UINT16, this->was_closed);
    this->cliente.sendall(&y_net, TAMANIO_UINT16, this->was_closed);

    return EXITO;
}

int ClientProtocolo::recibir_respuesta(){
    uint8_t respuesta;

    this->cliente.recvall(&respuesta, TAMANIO_UINT8, this->was_closed);
    if (respuesta == FALLO) {
        imprimir_notificacion_de_error();
    } else {
        imprimir_notificacion_ok();
    }
    std::cout << std::endl;
    return EXITO;
}

void ClientProtocolo::imprimir_notificacion_ok(){
    std::cout << "Construccion Exitosa";
}


int ClientProtocolo::imprimir_notificacion_de_error(){
    std::cout << "Lugar Insuficiente. Posiciones bloqueadas: ";

    uint8_t cantidad_colisiones = 0;
    this->cliente.recvall(&cantidad_colisiones, TAMANIO_UINT8, this->was_closed);

    for (int i = 0; i < cantidad_colisiones; i++) {
        uint16_t colision_x = 0, colision_y = 0;
        this->cliente.recvall(&colision_x, TAMANIO_UINT16, this->was_closed);
        uint16_t colision_x_net = ntohs(colision_x);

        this->cliente.recvall(&colision_y, TAMANIO_UINT16, this->was_closed);
        uint16_t colision_y_net = ntohs(colision_y);

        std::cout << "(" << colision_x_net << "," << colision_y_net << ") ";
    }
    return EXITO;
}
