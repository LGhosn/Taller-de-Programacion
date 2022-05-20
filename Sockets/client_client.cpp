#include "client_client.h"

#define FALLO 1
#define EXITO 0

Cliente::Cliente(char *host_name, char *service_name, char *archivo) : esta_cerrado(false), 
    protocolo_cliente(host_name, service_name, &this->esta_cerrado), archivo(archivo) {}

int Cliente::comunicar_con_servidor(){
    if (!this->archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return FALLO;
    }
    try {
        uint16_t edificio = 0,x = 0,y = 0;
        while (!this->esta_cerrado) {
            this->archivo >> edificio >> x >> y;
            if (this->archivo.eof()) {
                break;
            }

            uint8_t edificio_8 = edificio;
            protocolo_cliente.enviar_comando(edificio_8, x, y);
            protocolo_cliente.recibir_respuesta();
        }
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return FALLO;
    } catch (int e) {
        return EXITO;
    }
    return EXITO;
}
