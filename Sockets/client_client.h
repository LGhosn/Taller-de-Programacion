#include "common_socket.h"
#include "client_protocolo.h"
#include <fstream>
#include <iostream>

class Cliente{
private:
    bool esta_cerrado;
    ClientProtocolo protocolo_cliente;
    std::ifstream archivo;

public:
    /*
    * @param host_name: nombre del host
    * @param service_name: nombre del servicio
    * @param archivo: nombre del archivo
    */
    Cliente(char *host_name, char *service_name, char *archivo);

    /*
    * @return: 0 si se pudo comunicar con el servidor, 1 si no se pudo
    */
    int comunicar_con_servidor();
};

