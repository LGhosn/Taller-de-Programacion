#include <utility>
#include <iostream>

#include "server_manejador.h"
#include "common_socket_exceptions.h"

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/
void ManejadorCliente::verificar_union(part_t::iterator it, std::string nombre){
    if (it->second.agregar_jugador()){
        this->server_protocolo.operacion_exitosa();
        if (it->second.partida_llena()){
            this->server_protocolo.partida_completa(nombre);
        }
    } else {
        this->server_protocolo.operacion_fallida();
    }
}

void ManejadorCliente::unirse_a_partida(){
    datos_para_unirse_t datos=this->server_protocolo.recibir_para_unirse_partida();
    std::string nombre;
    uint8_t casa = 0;
    std::tie(nombre, casa) = datos;
    
    std::lock_guard<std::mutex> lock(this->mutex_partidas);
    part_t::iterator it = this->partidas->find(nombre);
    if (it == this->partidas->end()) {
        this->server_protocolo.operacion_fallida();
    } else {
        verificar_union(it, nombre);
    }
}

void ManejadorCliente::listar_partidas(){
    std::lock_guard<std::mutex> lock(this->mutex_partidas);
    uint8_t cantidad = this->partidas->size();
    this->server_protocolo.notificar_cantidad_partidas(cantidad);
    for (auto &partida : *this->partidas) {
        datos_partida_t datos = partida.second.ver_partida();
        this->server_protocolo.listar_partida(datos);
    }
}

void ManejadorCliente::crear_partida(){
    datos_partida_t datos = this->server_protocolo.recibir_para_crear_partida();
    std::string nombre;
    uint8_t largo_nombre = 0, casa = 0, capacidad = 0;
    std::tie(largo_nombre, nombre, casa, capacidad) = datos;

    std::lock_guard<std::mutex> lock(this->mutex_partidas);
    if (this->partidas->find(nombre) != this->partidas->end()) {
        this->server_protocolo.operacion_fallida();
    } else {
        Partida partida = Partida(largo_nombre, nombre, capacidad);
        this->partidas->insert(std::make_pair(nombre, partida));
        this->server_protocolo.operacion_exitosa();
    }
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

ManejadorCliente::ManejadorCliente(Socket &cliente,part_t *partidas,std::mutex &mutex_partidas):
    cliente(std::move(cliente)),esta_cerrado(false),
    server_protocolo(&this->cliente, &this->esta_cerrado),
    sigue_corriendo(true), partidas(partidas), 
    mutex_partidas(mutex_partidas) {
        this->hilo_cliente = std::thread(&ManejadorCliente::atender_cliente, this);
    }

bool ManejadorCliente::esta_inactivo() {
    bool res = this->sigue_corriendo;
    return !res;
}

void ManejadorCliente::atender_cliente() {
    uint8_t operacion = 0, unirse = 0x01, listar = 0x02, crear = 0x03;
    while (this->sigue_corriendo) {
        try {
            this->server_protocolo.recibir_operacion(&operacion);
            // Trate de aplicar un map con clave operacion y valor funcion
            // pero no logre hacer que funcionara. Como podria quitarme estos ifs? polimorfismo?
            if (operacion == unirse) {
                unirse_a_partida();
            } else if (operacion == listar) {
                listar_partidas();
            } else if (operacion == crear) {
                crear_partida();
            }
        }catch (SocketExceptions &e) {
            this->sigue_corriendo = false;
        }catch (...) {
            std::cout << "Error desconocido" << std::endl;
            return;
        }
    }
}

void ManejadorCliente::detener() {
    this->sigue_corriendo = false;
    this->cliente.shutdown(2);
    this->cliente.close();
}

ManejadorCliente::~ManejadorCliente() {
    this->hilo_cliente.join();
}
