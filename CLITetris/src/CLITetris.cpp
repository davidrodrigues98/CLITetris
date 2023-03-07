// CLITetris.cpp : Defines the entry point for the application.
#include <CLITetris.h>
#include <Game.h>
#include <Printer.h>

using namespace std;

DWORD gFdwMode, gFdwOldMode;

// Flags and structures that will be used in multiple threads.
atomic<bool> gTerminateGameUpdaterThread(false), gGameUpdaterInputEnabled(false);
atomic<KeyBind> gNextAction(IDLE);

KeyBind KeyEventProc(KEY_EVENT_RECORD ker)
{
	WORD recordedKeyCode = ker.wVirtualKeyCode;
	KeyBind result = IDLE;

	// Virtual key mapping.
	switch (recordedKeyCode)
	{
	case 37: result = LEFT; break;
	case 38: result = UP;  break;
	case 39: result = RIGHT; break;
	case 40: result = DOWN; break;
	}

	return result;
}

long win32_TimeStep(Game *_gameInstance, HANDLE _hStdIn, DWORD& _cNumRead, INPUT_RECORD(&_irInBuf)[INPUT_RECORD_BUFFER_SIZE]) {
	wprintf(L"Debug -> win32_TimeStep");
	long result = WaitForSingleObject(_hStdIn, /*gGameRules.GAME_SPEED_S **/ 1000);
	switch(result)
	{
	case WAIT_OBJECT_0:
		ReadConsoleInput(
			_hStdIn,
			_irInBuf,
			INPUT_RECORD_BUFFER_SIZE,
			&_cNumRead
		);
		if (_irInBuf[_cNumRead - 1].Event.KeyEvent.bKeyDown)
			gNextAction = KeyEventProc(_irInBuf[_cNumRead - 1].Event.KeyEvent);
		break;
	case WAIT_TIMEOUT:
		gNextAction = IDLE;
		break;
	default:
		gNextAction = IDLE;
		break;
	};
	FlushConsoleInputBuffer(_hStdIn);
	return result;
}

/// <summary>
/// Processes the game time loop with multi-threading.
/// </summary>
/// <returns>0</returns>
void GameUpdater(int _time_ms, Game *_instance) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf[INPUT_RECORD_BUFFER_SIZE];
	DWORD cNumRead;
	do {
		while (gGameUpdaterInputEnabled == true)
		{
			this_thread::sleep_for(chrono::milliseconds(_time_ms));
			win32_TimeStep(_instance, hStdIn, cNumRead, irInBuf);
			//? wprintf(L"%s\n", stringify(gNextAction));
			//_instance->Update();
		}
	} while (gTerminateGameUpdaterThread == false);
}

void ManageConsoleMode(bool _gameMode) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (_gameMode == true) {
		DWORD cNumRead;
		GetConsoleMode(hStdIn, &gFdwOldMode);
		// disable mouse and window input
		gFdwMode = ENABLE_INSERT_MODE || ENABLE_WINDOW_INPUT;
		SetConsoleMode(hStdIn, gFdwMode);
	}
	else
		SetConsoleMode(hStdIn, gFdwOldMode);
}

int BeforeInitialize() {
	int res = 0;
	_setmode(_fileno(stdout), _O_U8TEXT);
	res++;
	return res;
}

int devInitialize() {
	
	ManageConsoleMode(true);
	Game* gameInstance = new Game();
	thread t(GameUpdater, 400, gameInstance);
	gGameUpdaterInputEnabled = true;
	t.join();
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
