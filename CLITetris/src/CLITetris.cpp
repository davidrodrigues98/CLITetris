// CLITetris.cpp : Defines the entry point for the application.
#include <CLITetris.h>
#include <Game.h>

using namespace std;

DWORD gFdwMode, gFdwOldMode;

// Flags and structures that will be used in multiple threads.
atomic<bool> terminateGameThreads_(false);//, gGameUpdaterInputEnabled(false);

/// <summary>
/// Waits for next windows keyboar input event and handles it accordigly.
/// </summary>
/// <param name="_gameInstance">Created game instance to be send the data.</param>
/// <param name="_hStdIn">win Event handler</param>
/// <returns></returns>
KeyBind win32_TimeStep(Game *_gameInstance, HANDLE _hStdIn) {
	INPUT_RECORD irInBuf[INPUT_RECORD_BUFFER_SIZE];
	DWORD cNumRead;
	if (ReadConsoleInput(
		_hStdIn,
		irInBuf,
		128,
		&cNumRead
	)) 
	{
		for (int i = 0; i < cNumRead; i++) {
			if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
				return KeyEventProc(irInBuf[i].Event.KeyEvent);
			}
		}
	}
	return IDLE;
}

/// <summary>
/// Processes the game time loop with multi-threading.
/// </summary>
/// <param name="_instance">Current game object.</param>
void GameUpdater(Game *_instance) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	do {
		KeyBind nextAction = win32_TimeStep(_instance, hStdIn);
		_instance->Update(nextAction);
	} while (terminateGameThreads_ == false); //gTerminateGameUpdaterThread == false);
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
		terminateGameThreads_ = _instance->Update(KeyBind::DOWN);
	} while (terminateGameThreads_ == false);
}

/// <summary>
/// Thread function responsible for printing game visual input for the user.
/// </summary>
/// <param name="_time_ms">Loop time in ms for the process to occur.</param>
/// <param name="_instance">Current game object.</param>
void PrintCycle(int _time_ms, Game* _instance) {
	do {
		this_thread::sleep_for(chrono::milliseconds(_time_ms));
		_instance->PrintBoard();
	} while (terminateGameThreads_ == false);
}

void ManageConsoleMode(bool _gameMode) {
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (_gameMode == true) {
		DWORD cNumRead;
		GetConsoleMode(hStdIn, &gFdwOldMode);
		// disable mouse and window input
		gFdwMode = ENABLE_INSERT_MODE;
		SetConsoleMode(hStdIn, gFdwMode);
	}
	else
		SetConsoleMode(hStdIn, gFdwOldMode);
}

int BeforeInitialize() {
	int res = 0;
	//?_setmode(_fileno(stdout), _O_U8TEXT);
	setlocale(LC_CTYPE, "");
	res++;
	return res;
}

void GameOver(Game* _gameInstance) {

	// Free game instance.
	delete _gameInstance;
	system("pause");
}

int StartGame() {
	// Configures CLI
	ManageConsoleMode(true);

	// Initializes the screen, sets up memory and clears the screen.
	WINDOW *win = initscr();

	// Starts new game object.
	Game* gameInstance = new Game(true);
	
	// Starts the game directly.
	gameInstance->StartGame();
	// Declares array of threads to run tasks simultaneously.
	vector<thread> threads;

	// Start threads.
	threads.push_back(thread(AutoStepDown, 200, gameInstance));
	threads.push_back(thread(GameUpdater, gameInstance));
	threads.push_back(thread(PrintCycle, 10, gameInstance));

	// Join them.
	for (auto& thread : threads) {
		thread.join();
	}

	endwin();

	// This section only happens when the game is over.
	GameOver(gameInstance);

	return 0;
}

int defInitialize() {
	std::vector<std::string> options = { "Play", "Exit" };
	Menu menu(options);
	int result = menu.Run();
	switch (result) {
	case 1:
		StartGame();
		break;
	}
	return 0;
}

int Initialize(bool _dev) {
	if (_dev)
		StartGame();
	else
		defInitialize();
	return 0;
}

// Program starts here.
int main()
{
	BeforeInitialize();
	Initialize();
}
