#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <tuple>
#include <memory>

class Mapa {
private:
    int ancho;
    int alto;
    std::vector< std::vector<char> > mapa;
    std::vector< std::tuple<int, int> > colisiones;

    /*
     * Dado un edificio, devuelve la cantidad de casillas que ocupa y el tipo de edificio que es 
     * @param edificio: edificio a construir
    */
    std::tuple<int, int, char> propiedades_edificio(uint8_t edificio);

    /*
     * Verifica que no haya colisiones con el edificio a construir, si las hay las agrega a la lista de colisiones
     * @param pos_x: posicion en x de donde se quiere colocar el edificio
     * @param pos_y: posicion en y de donde se quiere colocar el edificio 
     * @param dimension_x: dimension en x del edificio
     * @param dimension_y: dimension en y del edificio
    */
    bool hay_colisiones(uint16_t pos_x, uint16_t pos_y, int dimension_x, int dimension_y);

    /*
     * Edifica el edificio en el mapa en caso de ser posible
     * @param pos_x: posicion en x de donde se quiere colocar el edificio
     * @param pos_y: posicion en y de donde se quiere colocar el edificio 
     * @param propiedades_edif: propiedades del edificio a construir <dimension_x, dimension_y, tipo_edificio>
    */
    void edificar(uint16_t pos_x, uint16_t pos_y, std::tuple<int, int, char> propiedades_edif);

public:
    /*
     * Construye un mapa de ancho x alto
     *@param ancho Ancho del mapa
     *@param alto Alto del mapa
    */
    Mapa(int ancho, int alto);

    //Hago este typedef para no superar los 100 caracteres y que no haya problemas con cpplint
    typedef std::tuple<uint8_t, uint16_t, uint16_t> comando_t;
    /*
     * Coloca un edificio en el mapa en caso de ser posible
     *@param comando una tupla conformada por el edificio(uint8_t), la coordenada x(uint16_t) y la coordenada y(uint16_t)
     *@return un vector de tuplas con las coordenadas en las que se colisiono, si no hubo colision devuelve un vector vacio
     */
    bool construir_edificio(comando_t comando);

    /*
     * Imprime el mapa en consola
    */
    void imprimir();

    std::vector< std::tuple<int, int> > ver_colisiones();

    // Destructor del mapa
    ~Mapa() = default;

    /* 
     * Copiar y/o asignar un mapa que esta ligado a un servidor no tiene sentido
    */
    Mapa(const Mapa&) = delete;
    Mapa& operator=(const Mapa&) = delete;

    /*
     * Mapa es movible
    */
    Mapa(Mapa &&);
    Mapa &operator=(Mapa &&);
};

#endif
