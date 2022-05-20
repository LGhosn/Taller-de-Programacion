#include <algorithm>
#include <iostream>

#include "server_mapa.h"

#define TORRE_DE_AIRE 'T'
#define CUARTEL 'C'
#define SILO 'S'

enum dimensiones {
    una_dimension = 1,
    dos_dimensiones = 2,
    tres_dimension = 3
};

/* ******************************************************************
 *                        PRIVADAS
 * *****************************************************************/
std::tuple<int, int, char> Mapa::propiedades_edificio(uint8_t edificio) {
    int dimension_x = 0, dimension_y = 0;
    char tipo_edificio = 0;
    const uint8_t torre = 0x01, cuartel = 0x02, silo = 0x03;
    switch (edificio) {
        case torre:
            dimension_x = tres_dimension;
            dimension_y = tres_dimension;
            tipo_edificio = TORRE_DE_AIRE;
            break;
        case cuartel:
            dimension_x = dos_dimensiones;
            dimension_y = tres_dimension;
            tipo_edificio = CUARTEL;
            break;
        case silo:
            dimension_x = una_dimension;
            dimension_y = una_dimension;
            tipo_edificio = SILO;
            break;
        default:
            std::cout << "Error: edificio no reconocido" << std::endl;
            break;
    }
    return std::make_tuple(dimension_x, dimension_y, tipo_edificio);
}

bool Mapa::hay_colisiones(uint16_t pos_x, uint16_t pos_y, int dimension_x, int dimension_y) {
    bool colision = false;
    for (int i = pos_y; i < pos_y + dimension_y; i++){
        for (int j = pos_x; j < pos_x + dimension_x; j++){
            // Verifico que el edificio no se salga del mapa
            if (j >= this->ancho || i >= this->alto){
                this->colisiones.push_back(std::make_tuple(j, i));
                colision = true;
                continue;
            }
            if (this->mapa[i][j] != '.'){
                this->colisiones.push_back(std::make_tuple(j, i));
                colision = true;
            }
        }
    }
    return colision;
}

void Mapa::edificar(uint16_t pos_x, uint16_t pos_y, std::tuple<int, int, char> propiedades) {
    int dimension_x = 0, dimension_y = 0;
    char tipo_edificio = 0;
    std::tie(dimension_x, dimension_y, tipo_edificio) = propiedades;
    if (this->colisiones.empty()){
        for (int i = pos_y; i < pos_y + dimension_y; i++){
            for (int j = pos_x; j < pos_x + dimension_x; j++){
                this->mapa[i][j] = tipo_edificio;                
            }
        }
    }
}

/* ******************************************************************
 *                        PUBLICAS
 * *****************************************************************/

Mapa::Mapa(int ancho, int alto) : ancho(ancho), alto(alto) {
    this->mapa = std::vector< std::vector<char> > (alto, std::vector<char>(ancho, '.'));
}

bool Mapa::construir_edificio(comando_t comando){
    // Cada vez que se intente construir un edificio, se limpia la lista de colisiones
    this->colisiones = std::vector< std::tuple<int, int> >();

    uint8_t edificio = 0;
    uint16_t pos_x = 0, pos_y = 0;
    std::tie(edificio, pos_x, pos_y) = comando;
    std::tuple<int, int, char> propiedades_del_edificio = propiedades_edificio(edificio);

    int dimension_x = 0, dimension_y = 0;
    char tipo_edificio = 0;
    std::tie(dimension_x, dimension_y, tipo_edificio) = propiedades_del_edificio;
    if (hay_colisiones(pos_x, pos_y, dimension_x, dimension_y)) {
        return false;
    }
    edificar(pos_x, pos_y, propiedades_del_edificio);
    return true;
}

void Mapa::imprimir() {
    for (int i = 0; i < this->alto; i++){
        for (int j = 0; j < this->ancho; j++){
            std::cout << this->mapa[i][j];
        }
        std::cout << std::endl;
    }
}

std::vector< std::tuple<int, int> > Mapa::ver_colisiones() {
    return this->colisiones;
}

Mapa::Mapa(Mapa&& otro) : ancho(otro.ancho), alto(otro.alto) {
    this->mapa = otro.mapa;
    otro.mapa = std::vector< std::vector<char> > (otro.alto);
}

Mapa& Mapa::operator=(Mapa&& mapa){
    // Caso de querer moverse asi mismo.
    if (this == &mapa){
        return *this;
    }

    // Transfiero los recursos del otro mapa al nuestro.
    this->ancho = mapa.ancho;
    this->alto = mapa.alto;
    this->mapa = mapa.mapa;

    // Limpio el otro mapa.
    mapa.alto = -1;
    mapa.ancho = -1;
    mapa.mapa = std::vector< std::vector<char> > (mapa.alto);
    
    return *this;
}

