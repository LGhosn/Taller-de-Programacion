#include "common_socket.h"
#include "server_mapa.h"
#include "server_protocolo.h"

class Server{
private:
    bool esta_cerrado;
    ServerProtocolo protocolo_server;
    Mapa mapa;

    /*
     * Le dice al mapa donde se quiere construir un edificio.
     * @param pos_x: coordenada x del edificio a construir
     * @param pos_y: coordenada y del edificio a construir
     * @param edificio: edificio a construir
     */
    void construir_en_el_mapa(uint16_t pos_x, uint16_t pos_y, uint8_t edificio);

public:
    /*
     * @param service_name: nombre del servicio
     * @param ancho: ancho del mapa
     * @param alto: alto del mapa
     */
    Server(char *service_name, int ancho, int alto);

    /*
     * @return: 0 si se pudo comunicar con el cliente, 1 si no se pudo
     */
    int comunicar_con_cliente();
};
