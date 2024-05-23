#include <iostream>
#include "connection.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
// Reciclado de gabinator desktop
#define size_transfer 1024

#define debug true
#if debug
#define print(x) std::cout << x << std::endl
#else
#define print(x)
#endif

#define port "23112"
std::vector<uchar> capture_screen()
{
    cv::Mat img;
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

    img.create(Height, Width, CV_8UC4);
    SelectObject(Chwnd, Bitmap);
    StretchBlt(Chwnd, 0, 0, Width, Height, Window, XScreen, YScreen, Width, Height, SRCCOPY);
    GetDIBits(Chwnd, Bitmap, 0, Height, img.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
    DeleteObject(Bitmap);
    DeleteDC(Chwnd);
    ReleaseDC(hWnd, Window);
    std::vector<uchar> buf;
    cv::imencode(".jpg", img, buf);
    return buf;
}

int main()
{

    unsigned int offset = 0;
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    SOCKET server = connect_server(port);
    if (server == INVALID_SOCKET)
    {
        error("no hay server al cual conectarse", WSAGetLastError());
    }
    while (true)
    {
        std::vector<uchar> image_data = capture_screen();

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
