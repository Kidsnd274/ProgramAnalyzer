#ifndef SPA_ENDOFFILEEXCEPTION_H
#define SPA_ENDOFFILEEXCEPTION_H
#include <exception>

class EndOfFileException : std::exception {
public:
    char * what ();
};


#endif //SPA_ENDOFFILEEXCEPTION_H
