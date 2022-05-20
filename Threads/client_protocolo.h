#ifndef CLIENT_PROTOCOLO_H
#define CLIENT_PROTOCOLO_H

#include <string>

#include "common_socket.h"

class ClienteProtocolo {
    bool *esta_cerrado;
    Socket cliente;

    /*
     * @brief Envia el comando de listar partidas al servidor
    */
    void listar(std::string argumento);

    /*
     * @brief Envia el comando de crear una partida al servidor
     * @param argumento: la casa, los requeridos y el nombre de la partida
    */
    void crear(std::string argumento);
    
    /*
     * @brief Envia el comando de unirse a una partida al servidor
     * @param argumento: el nombre de la partida a la que se unira
    */
    void unirse(std::string argumento);
    
    /*
     * @brief Determina la casa que se le pasa como argumento
     * @param casa: la casa que se quiere determinar
    */
    uint8_t determinar_casa(std::string casa);
    
    /*
     * @brief Serializa el argumento para crear y lo envía al servidor
     * @param argumento Argumento a serializar
    */
    void serializar_y_enviar_argumento_crear(std::string argumento);
    
    /*
     * @brief Serializa el argumento para unirse y lo envía al servidor
     * @param argumento Argumento a serializar
    */
    void serializar_y_enviar_argumento_unirse(std::string argumento);
    
    /*
     * @brief Envia el nombre de la partida al servidor
     * @param nombre_partida Nombre de la partida a enviar
     * @param largo_nombre Largo del nombre de la partida
    */
    void enviar_nombre_partida(std::string nombre_partida, uint16_t largo_nombre);
    
    /*
     * @brief Recibe el nombre de la partida del servidor
    */
    std::string recibir_nombre_partida();
    
    /*
     * @brief Recibe si se pudo unirse a la partida del servidor
     * e imprime el resultado en pantalla
    */
    void resultado_union();
    
    /*
     * @brief Recibe si se pudo crear la partida del servidor
     * e imprime el resultado en pantalla
    */
    void resultado_creacion();
    
    /*
     * @brief Recibe un listado de las partidas del servidor
    */
    void imprimir_partidas();
    
    /*
     * @brief imprime una partida por pantalla
    */
    void imprimir_partida();


public:
    /*
     * @brief Constructor de la clase
     * @param host_name: nombre del host al que se conecta
     * @param service_name: nombre del servicio al que se conecta
     * @param esta_cerrado: puntero a un booleano que indica si el cliente esta cerrado
    */
    ClienteProtocolo(char *host_name, char *service_name, bool *esta_cerrado);

    /*
     * @brief envia el mensaje correspondiente al servidor segun el comando
     * @param comando: el comando que se quiere enviar
     * @param argumento: el argumento que se quiere enviar
    */
    void enviar_mensaje(std::string comando, std::string argumento);

    ~ClienteProtocolo() = default;
};
#endif //CLIENT_PROTOCOLO_H
