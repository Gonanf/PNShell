#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "errors.hpp"
#pragma comment(lib, "Ws2_32.lib")

#define DEBUG_WV true
#if DEBUG_WV
#define Print_Line(x) std::cout << x << std::endl
#else
#define Print_Line(x)
#endif

SOCKET connect_server(u_short port)
{
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in hx;
        hx.sin_family = AF_INET;
        hx.sin_port = htons(port);
        hx.sin_addr.s_addr = inet_addr("127.0.0.1");

    int r = WSAConnect(server_socket, (sockaddr*)(&hx), sizeof(hx), NULL, NULL, NULL, NULL);
        if (r == SOCKET_ERROR)
        {
            closesocket(server_socket);
            server_socket = INVALID_SOCKET;
        }
    return server_socket;
}