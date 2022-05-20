// "Copyright 2022 - Taller de Programacion Catedra Veiga - Lautaro Ghosn"
#include <stdio.h>
#include <string.h>
#include "wordscounter.h"

#define DELIM_WORDS " ,.;:\n"
#define COMIENZO_PALABRA 0
#define DURANTE_PALABRA 1
#define FIN_TEXTO 2

Wordscounter::Wordscounter() {
    this->words = 0;
}

size_t Wordscounter::get_words() {
    return this->words;
}

int Wordscounter::process(std::istream& text_file) {
    if (text_file.fail()) {
        return -1;
    }

    char state = COMIENZO_PALABRA;

    while (state != FIN_TEXTO) {
        char c = text_file.get();
        state = next_state(state, c);
    }

    return 0;
}

char Wordscounter::next_state(char state, char c) {
    char next_state = state;

    if (state == COMIENZO_PALABRA) {
        if (c == EOF) {
            next_state = FIN_TEXTO;
        } else if (strchr(DELIM_WORDS, c) == NULL) {
            next_state = DURANTE_PALABRA;
        }
    } else if (state == DURANTE_PALABRA) {
        if (c == EOF) {
            words++;
            next_state = FIN_TEXTO;
        } else if (strchr(DELIM_WORDS, c) != NULL) {
            words++;
            next_state = COMIENZO_PALABRA;
        }
    }

    return next_state;
}
