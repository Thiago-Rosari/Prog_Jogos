#include <windows.h>   // arquivo de cabeçalho mestre

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPSTR lpCmdLine,
					 _In_ int nCmdShow)
{
	MessageBox(NULL, "Olá, Windows!", "Mensagem", 1);

	return 0;
}


// APIENTRY  => diz ao compilador como passar argumentos para WinMain
// _In_ e _In_opt  => fazem parte da linguagem de anotação de código-fonte da Microsoft

// hInstance      => número para identificar a aplicação
// hPrevInstance  => número sempre nulo / não é mais usado
// lpCmdLine      => linha de comando passada na chamada do programa
// nCmdShow       => define como o programa deve ser inicializado (maximizado, minimizado, tela cheia)
 