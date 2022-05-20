#ifndef SERVER_PROTOCOLO_H
#define SERVER_PROTOCOLO_H
#include "common_socket.h"
#include <vector>
#include <tuple>

class ServerProtocolo{
private:
    Socket server;
    Socket cliente;
    bool *was_closed;
    
    /*
     * Envia al cliente las colisiones que hubo en el mapa.
     * @param colisiones Vector de tuplas con las colisiones que hubo en el mapa.
    */
    void enviar_colisiones(std::vector< std::tuple<int, int> > colisiones);
    
public:
    /*
     * Construye una nueva instancia de Protocolo.
     */
    explicit ServerProtocolo(char *service_name, bool *was_closed);

    /*
     * Recibe un comando del cliente.
     *
     * @param socket Socket con el que se comunica con el servidor.
     * @param was_closed Indica si el socket fue cerrado.
     * @return 0 si el comando se recibió correctamente, 1 si hubo un error al recibir o si se cerró el socket.
     */
    int recibir_comando(uint8_t *edificio, uint16_t *x, uint16_t *y);

    /*
     * Envía una notificación de error al cliente.
     *
     * @param socket Socket con el que se comunica con el cliente.
     * @param was_closed Indica si el socket fue cerrado.
     * @return 0 si la respuesta se envía correctamente, 1 si hubo un error al enviar o si se cerró el socket.
     */
    int notificar_error(std::vector< std::tuple<int, int> > colisiones);

    /*
     * Envía una notificación de que salió todo bien al cliente.
     *
     * @param socket Socket con el que se comunica con el cliente.
     * @param was_closed Indica si el socket fue cerrado.
     * @return 0 si la respuesta se envía correctamente, 1 si hubo un error al enviar o si se cerró el socket.
     */
    int notificar_ok();
};

#endif
