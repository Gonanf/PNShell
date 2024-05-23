#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

SOCKET connect_server(char* port)
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