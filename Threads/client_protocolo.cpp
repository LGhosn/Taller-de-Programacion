#include <vector>
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <map>

#include "client_protocolo.h"

#define OP_EXITO 0X00
#define SIZEOF_BYTE 1
#define SIZEOF_TWO_BYTES 2

enum mensajes_t {
    m_unir = 0x01,
    m_listar = 0x02,
    m_crear = 0x03,
};

enum casas_t {
    harkonnen = 0x00,
    atreides = 0x01,
    ordos = 0x02,
};

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/

void ClienteProtocolo::unirse(const std::string argumento) {
    uint8_t mensaje_unir = m_unir;
    cliente.sendall(&mensaje_unir, SIZEOF_BYTE, this->esta_cerrado);
    serializar_y_enviar_argumento_unirse(argumento);
}

void ClienteProtocolo::listar(const std::string argumento) {
    uint8_t mensaje_listar = m_listar;
    cliente.sendall(&mensaje_listar, SIZEOF_BYTE, this->esta_cerrado);
}

void ClienteProtocolo::crear(const std::string argumento) {
    uint8_t mensaje_crear = m_crear;
    cliente.sendall(&mensaje_crear, SIZEOF_BYTE, this->esta_cerrado);
    serializar_y_enviar_argumento_crear(argumento);
}

void ClienteProtocolo::serializar_y_enviar_argumento_crear(std::string argumento) {
    std::istringstream parseo(argumento);
    std::string casa,requeridos, nombre_partida;

    parseo >> casa >> requeridos >> std::ws;
    std::getline(parseo, nombre_partida);

    uint8_t num_requeridos = std::stoul(requeridos);
    uint8_t casa_num = determinar_casa(casa);
    uint16_t largo_nombre = nombre_partida.length();

    cliente.sendall(&casa_num, SIZEOF_BYTE, this->esta_cerrado);
    cliente.sendall(&num_requeridos, SIZEOF_BYTE, this->esta_cerrado);

    enviar_nombre_partida(nombre_partida, largo_nombre);
}

void ClienteProtocolo::serializar_y_enviar_argumento_unirse(std::string argumento) {
    std::istringstream parseo(argumento);
    std::string casa, nombre_partida;

    parseo >> casa >> std::ws;
    std::getline(parseo, nombre_partida);

    uint8_t casa_num = determinar_casa(casa);
    uint16_t largo_nombre = nombre_partida.length();

    cliente.sendall(&casa_num, SIZEOF_BYTE, this->esta_cerrado);

    enviar_nombre_partida(nombre_partida, largo_nombre);
}

void ClienteProtocolo::enviar_nombre_partida(std::string nombre_partida, uint16_t largo_nombre) {
    uint16_t largo_nombre_net = htons(largo_nombre);
    cliente.sendall(&largo_nombre_net, SIZEOF_TWO_BYTES, this->esta_cerrado);

    // Necesario este buffer porque al querer enviar un string, 
    // no hay forma de acceder al buffer interno
    // por lo que termina enviado basura, de esta forma corrijo ese problema.
    std::vector<char> buffer(nombre_partida.begin(), nombre_partida.end());
    cliente.sendall(buffer.data(), largo_nombre, this->esta_cerrado);
}

void ClienteProtocolo::resultado_union(){
    uint8_t resultado = 0;
    cliente.recvall(&resultado, SIZEOF_BYTE, this->esta_cerrado);
    if (resultado == OP_EXITO){
        std::cout << "Union exitosa" << std::endl;
    } else {
        std::cout << "Union fallida" << std::endl;
    }
}

void ClienteProtocolo::resultado_creacion(){
    uint8_t resultado = 0;
    cliente.recvall(&resultado, SIZEOF_BYTE, this->esta_cerrado);
    if (resultado == OP_EXITO){
        std::cout << "Creacion exitosa" << std::endl;
    } else {
        std::cout << "Creacion fallida" << std::endl;
    }
}

void ClienteProtocolo::imprimir_partidas(){
    uint16_t cantidad_partidas = 0;
    cliente.recvall(&cantidad_partidas, SIZEOF_TWO_BYTES, this->esta_cerrado);
    cantidad_partidas = ntohs(cantidad_partidas);
    for (int i = 0; i < cantidad_partidas; i++){
        imprimir_partida();
    }
}

void ClienteProtocolo::imprimir_partida() {
    uint8_t cantidad = 0, capacidad = 0;
    this->cliente.recvall(&cantidad, SIZEOF_BYTE, this->esta_cerrado);
    this->cliente.recvall(&capacidad, SIZEOF_BYTE, this->esta_cerrado);
    
    std::string nombre = recibir_nombre_partida();

    std::string formato = nombre + " " + std::to_string((int)cantidad) + "/";
    formato += std::to_string((int)capacidad);
    std::cout << formato << std::endl;
}

std::string ClienteProtocolo::recibir_nombre_partida(){
    uint16_t tamanio_nombre = 0;
    this->cliente.recvall(&tamanio_nombre, SIZEOF_TWO_BYTES, this->esta_cerrado);
    tamanio_nombre = ntohs(tamanio_nombre);

    // Necesario este buffer porque al querer recibir un string, 
    // no hay forma de acceder al buffer interno
    // por lo que termina recibiendo basura, de esta forma corrijo ese problema.
    std::vector<char> buffer(tamanio_nombre);
    this->cliente.recvall(buffer.data(), tamanio_nombre, this->esta_cerrado);
    std::string nombre(buffer.begin(), buffer.end());

    return nombre;
}

uint8_t ClienteProtocolo::determinar_casa(const std::string casa) {
    // Uso un map para que quede mas prolijo y ademas el 'at' lanza un error si no existe la clave
    // No aplico todavia polimorfismo porque para este sprint no lo veo necesario.
    std::map<std::string, uint8_t> casas = {
        {"Harkonnen", harkonnen},
        {"Atreides", atreides},
        {"Ordos", ordos},
    };
    return casas.at(casa);
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

ClienteProtocolo::ClienteProtocolo(char *host_name, char *service_name, bool *esta_cerrado) :
    esta_cerrado(esta_cerrado), cliente(host_name, service_name) {}

void ClienteProtocolo::enviar_mensaje(const std::string comando, const std::string argumento) {
    if (comando == "unirse") {
        unirse(argumento);
        resultado_union();
    } else if (comando == "listar") {
        listar(argumento);
        imprimir_partidas();
    } else if (comando == "crear") {
        crear(argumento);
        resultado_creacion();
    }
}
