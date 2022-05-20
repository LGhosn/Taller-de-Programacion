// "Copyright 2022 - Taller de Programacion Catedra Veiga - Lautaro Ghosn"
#include <iostream>
#include "wordscounter.h"

#define EXITO 0
#define FALLO 1

int main(int argc, char* argv[]) {
    Wordscounter* counter = new Wordscounter;
    if (!counter) {
        std::cerr << "Error: no se pudo crear el contador de palabras." << "\n";
        return FALLO;
    }

    std::ifstream *input = new std::ifstream;
    if (!input) {
        std::cerr << "Error: no se pudo crear el archivo de entrada." << "\n";
        delete(counter);
        return FALLO;
    }

    if (argc > 1) {
        input->open(argv[1]);
        if (counter->process(*input) == -FALLO) {
            delete(input);
            delete(counter);
            return FALLO;
        }
        input->close();
    } else {
        counter->process(std::cin);
    }
    size_t words = counter->get_words();

    delete counter;
    delete input;

    std::cout << words << std::endl;
    return EXITO;
}
