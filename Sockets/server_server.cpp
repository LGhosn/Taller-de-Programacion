#include "server_server.h"

#include <iostream>

#define FALLO 1
#define EXITO 0

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/

void Server::construir_en_el_mapa(uint16_t pos_x, uint16_t pos_y, uint8_t edificio){
    if (!this->mapa.construir_edificio(std::make_tuple(edificio, pos_x, pos_y))) {
       this->protocolo_server.notificar_error(this->mapa.ver_colisiones());

    } else {
       this->protocolo_server.notificar_ok();
    }
    this->mapa.imprimir();
    std::cout << std::endl;
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

Server::Server(char *service_name, int ancho, int alto) : 
    esta_cerrado(false), protocolo_server(service_name, &this->esta_cerrado), mapa(ancho, alto){}

int Server::comunicar_con_cliente(){
    uint8_t edificio = 0;
    uint16_t pos_x = 0, pos_y = 0;
    try {
        while (!this->esta_cerrado) {
            this->protocolo_server.recibir_comando(&edificio, &pos_x, &pos_y);
            
            construir_en_el_mapa(pos_x, pos_y, edificio);
        }
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return FALLO;
    } catch (int e) {
        return EXITO;
    }
    return EXITO;
}
