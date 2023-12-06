#include <windows.h>   // arquivo de cabe�alho mestre

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPSTR lpCmdLine,
					 _In_ int nCmdShow)
{
	MessageBox(NULL, "Ol�, Windows!", "Mensagem", 1);

	return 0;
}


// APIENTRY  => diz ao compilador como passar argumentos para WinMain
// _In_ e _In_opt  => fazem parte da linguagem de anota��o de c�digo-fonte da Microsoft

// hInstance      => n�mero para identificar a aplica��o
// hPrevInstance  => n�mero sempre nulo / n�o � mais usado
// lpCmdLine      => linha de comando passada na chamada do programa
// nCmdShow       => define como o programa deve ser inicializado (maximizado, minimizado, tela cheia)
 