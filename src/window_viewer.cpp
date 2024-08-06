#include <iostream>
#include "connection.hpp"
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define size_transfer 1024

#define debug true
#if debug
#define print(x) std::cout << x << std::endl
#else
#define print(x)
#endif

#define port 23112

static void custom_stbi_write_mem(void *context, void *data, int size) {
   auto& buffer = *static_cast<std::vector<uint8_t>*>(context);
    buffer.insert(buffer.end(), static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);
}

std::vector<uint8_t> capture_screen()
{
    HWND hWnd = GetDesktopWindow();
    HDC Window = GetDC(hWnd);
    HDC Chwnd = CreateCompatibleDC(Window);
    SetStretchBltMode(Chwnd, COLORONCOLOR);
    int Scale = 1;
    int XScreen = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int YScreen = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int Width = GetSystemMetrics(SM_CXSCREEN);
    int Height = GetSystemMetrics(SM_CYSCREEN);
    HBITMAP Bitmap = CreateCompatibleBitmap(Window, Width, Height);
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Width;
    bi.biHeight = -Height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SelectObject(Chwnd, Bitmap);
    BitBlt(Chwnd,0,0,Width,Height,Window,0,0,SRCCOPY|CAPTUREBLT);
    if (GetDIBits(Chwnd, Bitmap, 0, 0, NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS) == 0) std::cerr << "Error obteniendo header";
    bi.biCompression = BI_RGB;  
    std::cout << "TAM: " << bi.biSizeImage <<"\n";
    BYTE* buf = new BYTE[bi.biSizeImage];
    ZeroMemory(buf,bi.biSizeImage);
    if (GetDIBits(Chwnd, Bitmap, 0, bi.biHeight, (LPVOID)buf, (BITMAPINFO *)&bi, DIB_RGB_COLORS) == 0) std::cerr << "Error obteniendo buffer";
    DeleteObject(Bitmap);
    DeleteDC(Chwnd);
    ReleaseDC(hWnd, Window);

    std::vector<uint8_t> jpeg_buffer;
    int jpeg_quality = 90;
    int jpeg_size = stbi_write_jpg_to_func(
        custom_stbi_write_mem,
        &jpeg_buffer,
        Width, Height, 4, buf, jpeg_quality);
    return jpeg_buffer;
}



int main()
{
    unsigned int offset = 0;
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET server = connect_server(port);
    if (server == INVALID_SOCKET)
    {
        error("no hay server al cual conectarse", server);
    }
    while (true)
    {
        std::vector<uint8_t> image_data = capture_screen();
        unsigned char bytes[8];
        size_t n = image_data.size();
        memcpy(bytes, &n, 8);
        for (int i = 0; i < sizeof(n); i++)
        {
            image_data.insert(image_data.begin() + i, bytes[i]);
        }

        if (send(server, (char *)image_data.data(), image_data.size(), 0) < 0)
        {
            closesocket(server);
            WSACleanup();
            error("no se pudo enviar los datos de imagen", WSAGetLastError());
        }
    }
}
