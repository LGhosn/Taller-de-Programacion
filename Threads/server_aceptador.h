#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <thread>
#include <atomic>

#include "common_socket.h"
#include "server_manejador.h"

class Aceptador {
private:
    Socket server;
    std::thread hilo_aceptador;
    std::atomic<bool> sigue_corriendo;
    std::vector<ManejadorCliente*> manejadores_clientes;
    std::mutex mutex_clientes;

    typedef std::map<std::string, Partida> partidas_t;
    partidas_t partidas;

    /*
     * @brief Limpia los manejadores de clientes que no estén activos
    */
    void limpiar_manejadores();

    /*
     * @brief Destruye los manejadores de clientes
    */
    void destruir_manejadores();

    /*
     * @brief Determina el estado del manejador de cliente
     * @param manejador: El manejador de cliente
     * @return true si el manejador de cliente está inactivo, false en caso contrario
    */
    static bool manejador_inactivo(ManejadorCliente *manejador);

public:
    /*
     * @brief Constructor
     * @param service_name: El nombre del servicio
    */
    explicit Aceptador(char *service_name);

    /*
     * @brief Acepta clientes
    */
    void aceptar_clientes();

    /*
     * @brief Detiene el hilo de aceptación de clientes
    */
    void detener();

    /*
     * @brief Destructor
    */
    ~Aceptador();
};
#endif //SERVER_ACEPTADOR_H
