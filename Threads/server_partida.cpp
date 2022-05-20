#include "server_partida.h"

Partida::Partida(uint16_t largo_nombre, const std::string nombre, int capacidad) :
    largo_nombre(largo_nombre), nombre(nombre), cantidad(1), capacidad(capacidad) {}

datos_partida_t Partida::ver_partida() {
    return std::make_tuple(this->largo_nombre, this->nombre, this->cantidad, this->capacidad);
}

bool Partida::agregar_jugador() {
    if (this->cantidad < this->capacidad) {
        ++this->cantidad;
        return true;
    }
    return false;
}

bool Partida::partida_llena() {
    return this->cantidad == this->capacidad;
}
