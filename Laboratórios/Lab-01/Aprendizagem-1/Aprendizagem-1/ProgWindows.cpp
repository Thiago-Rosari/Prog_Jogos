/**********************************************************************************
// ProgWindows
//
// Cria��o:     06 Mai 2011
// Atualiza��o: 14 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Esqueleto b�sico de cria��o de uma janela no Windows
//              usando a API Win32. Este esqueleto pode ser usado como ponto
//              de partida para cria��o de qualquer aplica��o.
//
**********************************************************************************/

// inclui tipos b�sicos e fun��es da API Win32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// prot�tipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    HWND         hwnd;        // identificador da janela
    MSG          msg;         // mensagem
    WNDCLASS     wndclass;    // classe da janela

    // Definindo uma classe de janela chamada "BasicWindow" 
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WinProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_QUESTION);
    wndclass.hCursor = LoadCursor(NULL, IDC_CROSS);    // muda o estilo do cursor
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  // muda a cor de fundo da janela
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "BasicWindow";

    // Registrando a classe "BasicWindow"
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, "Erro na cria��o da janela!", "Aplica��o", MB_ICONERROR);
        return 0;
    }

    // Criando uma janela baseada na classe "BasicWindow" 
    hwnd = CreateWindow("BasicWindow",                // classe da janela
        "Aplica��o",                  // t�tulo da janela
        WS_OVERLAPPEDWINDOW,          // estilo da janela
        CW_USEDEFAULT,                // posi��o x inicial
        CW_USEDEFAULT,                // posi��o y inicial
        640,                // largura inicial
        480,                // altura inicial
        NULL,                         // identificador da janela pai
        NULL,                         // identificador do menu
        hInstance,                    // identificador da aplica��o
        NULL);                        // par�metros de cria��o

    
    ShowWindow(hwnd, nCmdShow);  // Mostra e atualiza a janela
    UpdateWindow(hwnd);          // Envia uma mensagem WM_PAINT para a janela


    // Tratamento de mensagens destinadas a janela da aplica��o
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // fim do programa
    return int(msg.wParam);
}

//-------------------------------------------------------------------------------

// procedimento da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC         hdc;      // representa o dispositivo gr�fico
    PAINTSTRUCT ps;       // guarda regi�o invalidada da janela
    RECT        rect;     // regi�o ret�ngular

    switch (message)
    {
    case WM_PAINT:
        // pega o contexto do dispositivo
        // HDC hdc = FetDC(hwnd)
           hdc = BeginPaint(hwnd, &ps);

        // define o ret�ngulo de destino
        // RECT rect = {0, 0, 100, 25}
           GetClientRect(hwnd, &rect);

        // mostra o texto na janela
        // TextOut(hdc, 50, 40, "Teste", -1)
           DrawText(hdc, "Oi Janela!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        
        // libera contexto do dispositivo
        // ReleaseDC(hwnd, hdc)
           EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//-------------------------------------------------------------------------------