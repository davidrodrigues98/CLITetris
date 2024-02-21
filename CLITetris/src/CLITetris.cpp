// CLITetris.cpp : Defines the entry point for the application.
#include <CLITetris.h>
#include <Game.h>

using namespace std;

DWORD gFdwMode, gFdwOldMode;

// Flags and structures that will be used in multiple threads.
atomic<bool> gTerminateGameUpdaterThread(false), gTerminateAutoStepDownThread(false);//, gGameUpdaterInputEnabled(false);
atomic<KeyBind> gNextAction(IDLE);

long win32_TimeStep(Game *_gameInstance, HANDLE _hStdIn, DWORD& _cNumRead, INPUT_RECORD(&_irInBuf)[INPUT_RECORD_BUFFER_SIZE]) {
	long result = WaitForSingleObject(_hStdIn, /*gGameRules.GAME_SPEED_S */ 500);
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
	return result;
}

/// <summary>
/// Processes the game time loop with multi-threading.
/// </summary>
/// <param name="_instance">Current game object.</param>
void GameUpdater(Game *_instance) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf[INPUT_RECORD_BUFFER_SIZE];
	DWORD cNumRead;
	do {
		win32_TimeStep(_instance, hStdIn, cNumRead, irInBuf);
		FlushConsoleInputBuffer(hStdIn);
		_instance->Update(gNextAction);
		
	} while (true); //gTerminateGameUpdaterThread == false);
}

/// <summary>
/// Force the tetromino piece to go "fall" 1 line.
/// </summary>
/// <param name="_time_ms">Loop time in ms for the process to occur.</param>
/// <param name="_instance">Current game object.</param>
void AutoStepDown(int _time_ms, Game* _instance) {
	do {
		this_thread::sleep_for(chrono::milliseconds(_time_ms));
		// Process the automatic down action of the active piece.
		_instance->Update(KeyBind::DOWN);
	} while (gTerminateAutoStepDownThread == false);
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
	// Configures CLI
	ManageConsoleMode(true);

	// Starts new game object.
	Game* gameInstance = new Game(true);
	
	// Starts the game directly.
	gameInstance->StartGame();
	// Declares array of threads to run tasks simultaneously.
	vector<thread> threads;

	// Start threads.
	threads.push_back(thread(AutoStepDown, 500, gameInstance));
	threads.push_back(thread(GameUpdater, gameInstance));

	// Join them.
	for (auto& thread : threads) {
		thread.join();
	}

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
