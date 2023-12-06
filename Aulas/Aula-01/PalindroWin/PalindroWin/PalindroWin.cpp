/**********************************************************************************
// PalindroWin
//
// Cria��o:     09 Jun 2011
// Atualiza��o: 14 Jul 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Exemplo de um programa completo para Windows. Exemplifica a
//              cria��o de bot�o, caixa de texto, r�tulo, caixa de grupo e
//              faz o tratamento da entrada do usu�rio. A aplica��o descobre
//              se uma palavra � um pal�ndromo.
//
**********************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>   // inclui cabe�alhos do windows

//----------------------------------------------------------------------------------

// Habilita estilos visuais modernos
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//---------------------------------------------------------------------------------

// Defini��es 
#define GROUPBOX_ID   100
#define LABEL_TEXT_ID 200
#define EDIT_TEXT_ID  300 
#define BUTTON_ID	  400

//--------------------------------------------------------------------------------

// Vari�veis globais 
bool      resultClean = true;      // tela de resultado est� limpa
HINSTANCE hInstanceApp;             // identificador da aplica��o
RECT      clientRect;               // dimens�es da �rea cliente da janela
HWND      hwndGroup;                // identificador para group box
HWND      hwndLabel;                // identificador para label 
HWND      hwndEdit;                 // identificador para edit control
HWND      hwndButton;               // identificador para button
HFONT     appFont;                  // fonte da aplica��o

//--------------------------------------------------------------------------------

// Prot�tipo do procedimento da janela
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------

// Programa principal
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    // define uma window class name
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WinProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "BasicWindow";

    // registra a nova class name
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, "Erro na cria��o da janela!", "Pal�ndromo", MB_ICONERROR);
        return 0;
    }

    // salvando identificador em vari�vel global
    hInstanceApp = hInstance;

    // usado para centralizar janela na tela
    int xWndPos = GetSystemMetrics(SM_CXSCREEN) / 2 - 200;
    int yWndPos = GetSystemMetrics(SM_CYSCREEN) / 2 - 120;

    // cria a janela principal
    hwnd = CreateWindow("BasicWindow",                  // classe da janela
        "Pal�ndromo",                   // t�tulo da janela
        WS_OVERLAPPED | WS_SYSMENU,     // estilo da janela
        xWndPos, yWndPos,               // posi��o x, y inicial
        400, 220,                       // largura e comprimento iniciais
        NULL,                           // identificador do objeto pai
        NULL,                           // identificador do menu
        hInstance,                      // identificador da aplica��o
        NULL);                          // par�metros de cria��o

    // mostra e atualiza a janela
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // entra no la�o principal de tratamento de eventos
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // traduz as mensagens
        TranslateMessage(&msg);

        // envia as mensagens para a "Window Procedure"
        DispatchMessage(&msg);
    }

    // finaliza programa
    return int(msg.wParam);
}

//------------------------------------------------------------------------------

// Gerenciador de mensagens do sistema
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT		ps;		// usado em WM_PAINT
    HDC				hdc;	// identificador de contexto do dispositivo

    switch (msg)
    {
    case WM_CREATE:

        // pega as dimens�es da janela para o posicionamento de objetos
        GetClientRect(hwnd, &clientRect);

        // Cria fonte MS Sans Serif
        appFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

        // Groupbox
        hwndGroup = CreateWindow(
            "BUTTON",                                   // classe
            "Resultado",                                // t�tulo
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,        // estilo do objeto
            clientRect.left + 10,                         // posi��o x inicial
            clientRect.top + 10,                          // posi��o y inicial
            clientRect.right - 20,                        // largura inicial
            100,                                        // comprimento inicial
            hwnd,                                       // identificador do pai 
            HMENU(GROUPBOX_ID),                        // identificador do objeto
            hInstanceApp,                               // identificador da aplica��o
            NULL);                                      // par�metros extras

        // Configura a fonte usada no Groupbox
        SendMessage(hwndGroup, WM_SETFONT, (WPARAM)appFont, TRUE);

        // Label
        hwndLabel = CreateWindowEx(
            NULL,                                       // estilos extras
            "STATIC",                                   // classe
            "Palavra:",                                 // t�tulo
            WS_CHILD | WS_VISIBLE,                      // estilo do objeto
            40, 140,                                     // posi��o x, y inicial
            140, 24,                                     // largura e comprimento inicial
            hwnd,                                       // identificador do pai
            HMENU(LABEL_TEXT_ID),                      // identificador do objeto
            hInstanceApp,                               // identificador da aplica��o
            NULL);                                      // par�metros extras

        // Configura a fonte usada no Label
        SendMessage(hwndLabel, WM_SETFONT, (WPARAM)appFont, TRUE);

        // Edit box
        hwndEdit = CreateWindowEx(
            WS_EX_CLIENTEDGE,                           // estilos extras
            "EDIT",                                     // classe
            "",                                         // t�tulo
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,     // estilo do objeto
            100, 138,                                    // posi��o x, y inicial
            130, 20,                                     // largura e comprimento inicial
            hwnd,                                       // manipulador pai
            HMENU(EDIT_TEXT_ID),                       // identificador do objeto
            hInstanceApp,                               // identificador da aplica��o
            NULL);                                      // par�metros extras

        // Configura a fonte usada na Edit box
        SendMessage(hwndEdit, WM_SETFONT, (WPARAM)appFont, TRUE);

        // Button
        hwndButton = CreateWindow(
            "BUTTON",                                   // classe
            "Verificar",                                // t�tulo
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,      // estilo do objeto
            255, 135,                                    // posi��o x, y inicial
            100, 24,                                     // largura e comprimento inicial
            hwnd,                                       // manipulador pai
            HMENU(BUTTON_ID),                          // identificador do objeto
            hInstanceApp,                               // identificador da aplica��o
            NULL);                                      // par�metros extra		

        SendMessage(hwndButton, WM_SETFONT, (WPARAM)appFont, TRUE);

        break;

    case WM_COMMAND:

        // se a caixa de texto foi modificada
        if (HIWORD(wParam) == EN_CHANGE)
        {
            // limpa a �rea de impress�o do resultado (se ela estiver suja)
            if (!resultClean)
            {
                // apaga resultado anterior
                RECT strRect = { clientRect.left + 20, clientRect.top + 40, clientRect.right - 20, clientRect.top + 90 };
                InvalidateRect(hwnd, &strRect, TRUE);
                UpdateWindow(hwnd);
                resultClean = true;
            }
        }

        // filtra pressionamento de bot�es
        switch (LOWORD(wParam))
        {

            // caso bot�o com identificador BUTTON_ID tenha sido pressionado
        case BUTTON_ID:

            // pega comprimento do texto armazenado na caixa de edi��o
            int strLen = GetWindowTextLength(hwndEdit);
            char* palavra = new char[strLen + 1];

            // pega texto da caixa de edi��o
            GetWindowText(hwndEdit, palavra, strLen + 1);

            // verifica se a palavra � pal�ndromo
            int i = 0;
            int j = strLen - 1;
            while (i < j && palavra[i] == palavra[j])
            {
                ++i;
                --j;
            }
            delete[] palavra;

            // pega contexto do dispositivo
            hdc = GetDC(hwnd);

            // cria a fonte Sans Serif
            appFont = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

            // seleciona nova fonte no contexto do dispositivo
            SelectObject(hdc, appFont);

            // fundo do texto tranparente
            SetBkMode(hdc, TRANSPARENT);

            // define regi�o de exibi��o do resultado 
            RECT strRect = { clientRect.left + 20, clientRect.top + 40, clientRect.right - 20, clientRect.top + 90 };

            // mostra resultado
            if (strLen == 0)
                DrawText(hdc, "Digite uma palavra", -1, &strRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            else
            {
                if (i >= j)
                    DrawText(hdc, "A palavra � um pal�ndromo", -1, &strRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                else
                    DrawText(hdc, "N�o � um pal�ndromo", -1, &strRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }


            // libera contexto do dispositivo
            ReleaseDC(hwnd, hdc);

            resultClean = false;
            break;
        }
        break;


    case WM_PAINT:
        // simplesmente valida a janela 
        hdc = BeginPaint(hwnd, &ps);

        // finaliza o desenho 
        EndPaint(hwnd, &ps);
        break;

    case WM_SETFOCUS:
        // a caixa de texto recebe o foco no inicio da aplica��o
        SetFocus(hwndEdit);
        return 0;

    case WM_DESTROY:
        // sai da aplica��o 
        PostQuitMessage(0);
        break;

    default:
        // processa qualquer mensagem n�o tratada pelos casos anteriores
        return (DefWindowProc(hwnd, msg, wParam, lParam));
    }

    // returna successo
    return 0;
}

//------------------------------------------------------------------------------