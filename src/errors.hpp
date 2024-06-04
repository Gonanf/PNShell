#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#pragma once

void error(const char *message, int type)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    exit(-1);
}

void sys_error(const char *message,const char* title){
    MessageBox(NULL,message,title,MB_ICONERROR | MB_OK);
    exit(-1);
}
