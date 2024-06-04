#include <iostream>
#include <fstream>
#include <string>
#include "errors.hpp"
#pragma once

std::string programs[] = {"libarbys.exe", "libwv.exe", "libval.exe"};

int main()
{
ShowWindow(GetConsoleWindow(),SW_HIDE);

    // Verificar si estan todos los archivos
    for (std::string i : programs)
    {
        std::ifstream program(i);
        if (!program.good())
        {
            std::string path;
            path = "falta el archivo " + i;
            error(path.c_str(), -1);
        }
    }

    // ejecutar todos los archivos
    for (std::string i : programs)
    {
        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION pi;
        if (!CreateProcess(NULL, (LPSTR)i.data(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
        {
            error("no se pudo crear los procesos de dependencias", GetLastError());
        }
    }


}