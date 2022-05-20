#ifndef SERVER_PARTIDAS_H
#define SERVER_PARTIDAS_H

#include <string>
#include <tuple>

typedef std::tuple<uint16_t, std::string, int, int> datos_partida_t;

class Partida{
private:
    uint16_t largo_nombre;
    std::string nombre;
    int cantidad;
    int capacidad;

public:
    /*
     * Crea una nueva partida
     * @param largo_nombre: largo del nombre de la partida
     * @param nombre: nombre de la partida
     * @param capacidad: capacidad maxima de la partida
    */
    Partida(uint16_t largo_nombre, std::string nombre, int capacidad);

    /*
     * Devuelve una tupla con los datos de la partida
     * en formato (largo_nombre, nombre, cantidad, capacidad)
     * @returns std::tuple<uint16_t, std::string, int, int>
    */
    datos_partida_t ver_partida();

    /*
     * Agrega un jugador a la partida en caso de ser posible
     * @returns true si se pudo agregar, false si no
    */    
    bool agregar_jugador();

    /*
     * Devuelve true si la partida está llena, false si no
     * @returns bool
    */
    bool partida_llena();

    ~Partida() = default;
};
#endif //SERVER_PARTIDAS_H
