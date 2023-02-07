// CLITetris.cpp : Defines the entry point for the application.
#include <CLITetris.h>
#include <Game.h>

using namespace std;

DWORD fdwMode, fdwOldMode;

int BeforeInitialize() {
	int res = 0;
	_setmode(_fileno(stdout), _O_U8TEXT);
	res++;
	return res;
}

void ManageConsoleMode(bool _gameMode) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf[2];
	DWORD cNumRead;
	GetConsoleMode(hStdIn, &fdwOldMode);
	// disable mouse and window input
	fdwMode = ENABLE_INSERT_MODE || ENABLE_WINDOW_INPUT;
	SetConsoleMode(hStdIn, fdwMode);
}

int devInitialize() {
	//? wprintf(L"Hello CMake.");
	Game* gameInstance = new Game(true);
	return 0;
}

int Initialize(bool _dev) {
	if (_dev)
		devInitialize();
	return 0;
}

// Program starts here.
int main()
{
	BeforeInitialize();
	Initialize(true);
}
