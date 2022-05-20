#ifndef CLIENT_PROTOCOLO_H
#define CLIENT_PROTOCOLO_H
#include "common_socket.h"
#include <vector>
#include <tuple>

class ClientProtocolo{
private:
    Socket cliente;
    bool *was_closed;
    /*
     * Imprime en el cliente la notificacion de que salió todo bien
    */
    void imprimir_notificacion_ok();

    /*
     * Recibe e imprime en el cliente la notificacion de que hubo un error
     * @param socket Socket que se usará para recibir la notificacion
     * @param was_closed Puntero a un bool que indica si el socket se cerró
     * @return 0 si se recibió correctamente, 1 si hubo un error al recibir el error o si el socket se cerró
    */
    int imprimir_notificacion_de_error();
    
public:
    /*
     * Construye una nueva instancia de Protocolo.
     */
    explicit ClientProtocolo(char *host_name, char *service_name, bool *was_closed);

    /*
     * Envía un comando al servidor.
     *
     * @param socket Socket con el que se comunica con el servidor.
     * @param edificio Edificio a construir.
     * @param x Coordenada x del edificio.
     * @param y Coordenada y del edificio.
     * @param was_closed Indica si el socket fue cerrado.
     * @return 0 si el comando se envía correctamente, 1 si hubo un error al enviar o si se cerró el socket.
     */
    int enviar_comando(uint8_t edificio, uint16_t x, uint16_t y);

    /*
     * Recibe una respuesta del comando enviado al servidor.
     *
     * @param socket Socket con el que se comunica con el servidor.
     * @param was_closed Indica si el socket fue cerrado.
     * @return 0 si la respuesta se envía correctamente, 1 si hubo un error al enviar o si se cerró el socket.
     */
    int recibir_respuesta();
};

#endif
