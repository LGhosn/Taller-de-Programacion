#include <arpa/inet.h>
#include <iostream>

#include "server_protocolo.h"

#define OP_EXITO 0X00
#define OP_FALLO 0X01
#define SIZEOF_BYTE 1
#define SIZEOF_TWO_BYTES 2

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/

std::string ServerProtocolo::recibir_nombre_partida(uint16_t *largo_nombre) {
    uint16_t tamanio_nombre = 0;
    this->comunicador->recvall(&tamanio_nombre, SIZEOF_TWO_BYTES, this->esta_cerrado);
    tamanio_nombre = ntohs(tamanio_nombre);
    *largo_nombre = tamanio_nombre;

    // Necesario este buffer porque al querer recibir un string, 
    // no hay forma de acceder al buffer interno
    // por lo que termina recibiendo basura, de esta forma corrijo ese problema.
    std::vector<char> buffer(tamanio_nombre);
    this->comunicador->recvall(buffer.data(), tamanio_nombre, this->esta_cerrado);
    std::string nombre(buffer.begin(), buffer.end());

    return nombre;
}

void ServerProtocolo::enviar_nombre(std::string nombre, uint16_t largo_nombre) {
    uint16_t largo_nombre_net = htons(largo_nombre);
    this->comunicador->sendall(&largo_nombre_net, SIZEOF_TWO_BYTES, this->esta_cerrado);

    // Necesario este buffer porque al querer enviar un string, 
    // no hay forma de acceder al buffer interno
    // por lo que termina enviado basura, de esta forma corrijo ese problema.
    std::vector<char> buffer(nombre.begin(), nombre.end());
    this->comunicador->sendall(buffer.data(), largo_nombre, this->esta_cerrado);
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

ServerProtocolo::ServerProtocolo(Socket *comunicador, bool *esta_cerrado) :
    comunicador(comunicador), esta_cerrado(esta_cerrado) {}

void ServerProtocolo::recibir_operacion(uint8_t *operacion) {
    this->comunicador->recvall(operacion, SIZEOF_BYTE, this->esta_cerrado);
}

datos_para_unirse_t ServerProtocolo::recibir_para_unirse_partida() {
    uint8_t casa = 0;
    uint16_t largo_nombre = 0;    
    this->comunicador->recvall(&casa, SIZEOF_BYTE, this->esta_cerrado);
    
    std::string nombre = recibir_nombre_partida(&largo_nombre);
    
    datos_para_unirse_t datos = {nombre, casa};
    return datos;
}

datos_partida_t ServerProtocolo::recibir_para_crear_partida() {
    uint8_t casa = 0, capacidad = 0;
    uint16_t largo_nombre = 0;
    
    this->comunicador->recvall(&casa, SIZEOF_BYTE, this->esta_cerrado);
    this->comunicador->recvall(&capacidad, SIZEOF_BYTE, this->esta_cerrado);

    std::string nombre = recibir_nombre_partida(&largo_nombre);  

    return std::make_tuple(largo_nombre, nombre, casa, capacidad);
}

void ServerProtocolo::operacion_fallida(){
    uint8_t fallo = OP_FALLO;
    this->comunicador->sendall(&fallo, SIZEOF_BYTE, this->esta_cerrado);
}

void ServerProtocolo::operacion_exitosa(){
    uint8_t exito = OP_EXITO;
    this->comunicador->sendall(&exito, SIZEOF_BYTE, this->esta_cerrado);
}

void ServerProtocolo::notificar_cantidad_partidas(uint16_t cantidad){
    uint16_t cantidad_net = htons(cantidad);
    this->comunicador->sendall(&cantidad_net, SIZEOF_TWO_BYTES, this->esta_cerrado);
}

void ServerProtocolo::listar_partida(datos_partida_t partida){
    std::string nombre;
    uint8_t cantidad = 0, capacidad = 0;
    uint16_t largo_nombre = 0;
    std::tie(largo_nombre, nombre, cantidad, capacidad) = partida;

    this->comunicador->sendall(&cantidad, SIZEOF_BYTE, this->esta_cerrado);
    this->comunicador->sendall(&capacidad, SIZEOF_BYTE, this->esta_cerrado);

    enviar_nombre(nombre, largo_nombre);
}

void ServerProtocolo::partida_completa(const std::string nombre){
    std::string formato = "Comenzando partida " + nombre + "...";
    std::cout << formato << std::endl;
}
