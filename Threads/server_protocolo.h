#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H

#include <string>
#include <vector>
#include <tuple>

#include "common_socket.h"

typedef std::tuple<uint16_t, std::string, int, int> datos_partida_t;

typedef std::tuple<std::string, uint8_t> datos_para_unirse_t;

class ServerProtocolo {
private:
    Socket *comunicador;
    bool *esta_cerrado;

    /*
     * @brief Recibe el nombre de la partida del cliente
     * y el largo del nombre, este ultimo se devuelve en el parametro largo_nombre.
     * @param largo_nombre: Largo del nombre de la partida.
     * @return El nombre de la partida.
    */
    std::string recibir_nombre_partida(uint16_t *largo_nombre);

    /*
     * @brief Envia el nombre de la partida al cliente
     * @param nombre Nombre de la partida a enviar
     * @param largo_nombre Largo del nombre de la partida
    */
    void enviar_nombre(std::string nombre, uint16_t largo_nombre);

public:
    /*
     * @brief Constructor de la clase.
     * @param esta_cerrado: Puntero que indica si el servidor esta cerrado.
     * @param comunicador: Puntero al socket del cliente.
    */
    ServerProtocolo(Socket *comunicador, bool *esta_cerrado);

    /*
     * @brief Recibe la operacion del cliente y la
     * setea en la variable operacion pasada por parametro
     * @param operacion: Variable que se setea con la operacion del cliente.
    */
    void recibir_operacion(uint8_t *operacion);

    /*
     * @brief Recibe y serializa las variables necesarias para unirse a una partida.
     * @return devuleve una tupla con el nombre de la partida y la casa.
    */
    datos_para_unirse_t recibir_para_unirse_partida();

    /*
     * @brief Recibe y serializa las variables necesarias para crear una partida.
     * @return devuleve una tupla con el largo del nombre, el nombre de la partida, la casa y la capacidad.
    */
    datos_partida_t recibir_para_crear_partida();
    
    /*
     * @brief Envia al cliente que fallo la operacion que se intento realizar.
    */
    void operacion_fallida();

    /*
     * @brief Envia al cliente que se pudo concreta la operacion que se intento realizar
    */
    void operacion_exitosa();

    /*
     * @brief Envia al cliente la cantidad partidas que hay.
     * @param cantidad: Cantidad de partidas que hay.
    */
    void notificar_cantidad_partidas(uint16_t cantidad);

    /*
     * @brief Envia al cliente una partida.
     * @param partida: Partida a ser enviada.
    */
    void listar_partida(datos_partida_t partida);

    /*
     * @brief Imprime por pantalla que la partida esta completa.
    */
    void partida_completa(std::string nombre);

    ~ServerProtocolo() = default;
};
#endif //SERVER_PROTOCOLO_H
