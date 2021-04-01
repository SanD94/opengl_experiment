#ifndef __CHECKERROR_H__
#define __CHECKERROR_H__

#include <iostream>
#include <string>
#include <GL/freeglut.h>


static std::string ErrorString(GLenum error) {
    std::string msg;
    switch(error) {
        #define Case(Token) case Token: msg = #Token; break;
        Case(GL_NO_ERROR);
        Case(GL_INVALID_VALUE);
        Case(GL_INVALID_ENUM);
        Case(GL_INVALID_OPERATION);
        Case(GL_STACK_OVERFLOW);
        Case(GL_STACK_UNDERFLOW);
        Case(GL_OUT_OF_MEMORY);
        #undef Case
    }
    return msg;
}


static void _CheckError(std::string file, int line) {
    GLenum error = glGetError();
    do {
        std::cerr << "[" << file << ":" << line << "] " 
            << ErrorString(error) << std::endl;
    } while((error = glGetError()) != GL_NO_ERROR);
}

#define CheckError() _CheckError(__FILE__, __LINE__)

#endif // __CHECKERROR_H__