/*#include <Main.h>

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
	//Game* gameInstance = new Game();
	return 0;
}

int Initialize(bool _dev) {
	if(_dev)
		devInitialize();
	return 0;
}*/
