#include <Game.h>

void ManageConsoleMode(bool _gameMode = true) {
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[N];
    DWORD cNumRead;
    GetConsoleMode(hStdIn, &fdwOldMode);
    // disable mouse and window input
    fdwMode = ENABLE_INSERT_MODE || ENABLE_WINDOW_INPUT;
    SetConsoleMode(hStdIn, fdwMode);
}

void Game::GenerateRandomTetrominoQueue(bool _officialRules = true) {

}