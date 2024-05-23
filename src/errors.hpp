#include <iostream>
#include <Windows.h>
#pragma once

void error(const char *message, int type)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    std::cin.get();
    exit(-1);
}

void sys_error(const char *message,const char* title){
    MessageBox(NULL,message,title,MB_ICONERROR | MB_OK);
    exit(-1);
}

void error_with_save(const char *message, int type,char* file_content)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    std::cin.get();
    exit(-1);
}