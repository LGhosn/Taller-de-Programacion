#ifndef SERVER_MANEJADOR_H
#define SERVER_MANEJADOR_H

#include <map>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>

#include "common_socket.h"
#include "server_protocolo.h"
#include "server_partida.h"

class ManejadorCliente {
private:
    Socket cliente;
    bool esta_cerrado;
    ServerProtocolo server_protocolo;
    std::atomic<bool> sigue_corriendo;
    std::thread hilo_cliente;

    typedef std::map<std::string, Partida> part_t;
    part_t *partidas;
    std::mutex &mutex_partidas;

    /*
     * @brief Trata que el cliente pueda unirse a la partida
    */
    void unirse_a_partida();

    /*
     * @brief Lista las partidas que hay en juego.
    */
    void listar_partidas();

    /*
     * @brief Crea una partida en caso de ser posible
     *  y da la respuesta correspondiente al cliente.
    */
    void crear_partida();

    /*
     * @brief Verifica que el cliente pueda unirse a la partida
     *  y da la resupesta correspondiente al cliente.
    */
    void verificar_union(part_t::iterator it, std::string nombre);

public:
    /*
     * @brief Constructor de la clase.
     * @param cliente Socket del cliente.
     * @param partidas Mapa de partidas.
     * @param mutex_partidas Mutex de la partidas.
    */
    ManejadorCliente(Socket &cliente, part_t *partidas, std::mutex &mutex_partidas);

    /*
     * @brief Atiende al cliente en base a la operacion recibida.
    */
    void atender_cliente();

    /*
     * @brief Detiene la comunicacion con el cliente.
    */
    void detener();

    /*
     * @brief Devuelve si el cliente esta inactivo.
     * @return True si el cliente esta inactivo, false en caso contrario.
    */
    bool esta_inactivo();

    /*
     * @brief Destructor de la clase.
    */
    ~ManejadorCliente();
};
#endif //SERVER_MANEJADOR_H
