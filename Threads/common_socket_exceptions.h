//
// Created by fedemgp on 3/4/22.
// https://github.com/Taller-de-Programacion/excepciones/tree/main/ej3
//

#ifndef COMMON_SOCKET_EXCEPTIONS_H
#define COMMON_SOCKET_EXCEPTIONS_H

#include <exception>

#define BUFF_LEN 256

class SocketExceptions: public std::exception {
private:
    char msg_error[BUFF_LEN];

public:
    SocketExceptions();
    
    SocketExceptions(const char *fmt, ...);

    virtual ~SocketExceptions() = default;
};


#endif //COMMON_SOCKET_EXCEPTIONS_H
