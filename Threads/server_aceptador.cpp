#include <algorithm>
#include <utility>
#include <iostream>

#include "server_aceptador.h"
#include "common_socket_exceptions.h"

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/

void Aceptador::limpiar_manejadores() {
    this->manejadores_clientes.erase(
        std::remove_if(this->manejadores_clientes.begin(), this->manejadores_clientes.end(),
            manejador_inactivo), this->manejadores_clientes.end());
}

void Aceptador::destruir_manejadores() {
    for (auto &manejador : this->manejadores_clientes) {
        manejador->detener();
        delete manejador;
    }
    this->manejadores_clientes.clear();
}

bool Aceptador::manejador_inactivo(ManejadorCliente *manejador) {
    if (manejador->esta_inactivo()) {
        delete manejador;
        return true;
    }
    return false;
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

Aceptador::Aceptador(char *service_name) : server(service_name), sigue_corriendo(true) {
    this->hilo_aceptador = std::thread(&Aceptador::aceptar_clientes, this);
}

void Aceptador::aceptar_clientes(){
    while (this->sigue_corriendo) {
        try {
            Socket aceptado = this->server.accept();
            this->manejadores_clientes.emplace_back(
                new ManejadorCliente(aceptado, &this->partidas, this->mutex_clientes));
            limpiar_manejadores();
        }catch (SocketExceptions &e) {
            this->sigue_corriendo = false;
        }catch (...) {
            std::cout << "Error desconocido" << std::endl;
            return;
        }
    }
    destruir_manejadores();
}

void Aceptador::detener() {
    this->sigue_corriendo = false;
    this->server.shutdown(2);
}

Aceptador::~Aceptador() {
    this->hilo_aceptador.join();
}
