#pragma once

#include <Piece.h>
#include <Printer.h>

#pragma region Auxiliary structures outside class definition
/// <summary>
/// Enumerator to process key mapping against the application.
/// </summary>
typedef enum KeyBind {
	DOWN,
	kbLEFT,
	kbRIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	IDLE // Special action for when an user doesn't press any key at a given time interval.
} KeyBind;

/// <summary>
/// Maps the key code (windows) to the enumerator interface in the program.
/// </summary>
/// <param name="ker">The windows "key pressed" event to process.</param>
/// <returns>Respective enumerator code.</returns>
KeyBind KeyEventProc(KEY_EVENT_RECORD ker);

/// <summary>
/// Structure to handle linked list queue management.
/// </summary>
typedef struct TetrominoNode {
	// Tetromino value.
	Tetromino value;
	TetrominoNode* next;
} TetrominoNode;

/// <summary>
/// Statistics and Game Score.
/// </summary>
typedef struct GameDetails {
	int score = 0;
} GameDetails;

/// <summary>
/// Enumerator to help describing the current game status.
/// </summary>
typedef enum GameStatus {
	PLACE, // The game just started or it's time to spawn a new piece.
	MOVE,  // A tetromino move is being performed.
	OVER,   // Conditions for game over are met.
	WAIT
} GameStatus;
#pragma endregion

/// <summary>
/// Class for game logic.
/// In game memory and steps validation.
/// Each instance is a round of a game.
/// </summary>
class Game {
protected:

#pragma region Properties
	int _lineSize;
	GameStatus gGameStatus;
	Printer::Visuals* _gameBoard = nullptr;
	BoardRules _boardRules;
	
	// Linked list pointers for the Tetromino spawning queue:
	TetrominoNode* gQueueHead = nullptr, * gQueueTail = nullptr, * gQueueCurrent = nullptr;
	
	/// <summary>
	/// Pointer reference to the piece being controlled at the moment.
	/// </summary>
	Piece* _activePiece = nullptr;
#pragma endregion

#pragma region Private methods
	/// <summary>
	/// Function that generates the starting pieces.
	/// </summary>
	/// <param name="_double_bag">true: Use double bag randomization. false: Use single bag randomization.</param>
	/// <param name="_print">(Optional) Printing debug for testing purposes.</param>
	void GenerateRandomTetrominoQueue(bool _double_bag, bool _print = false);

	/// <summary>
	/// Fetch the next tetromino type from the list.
	/// </summary>
	/// <returns>Next tetromino type for piece instancing.</returns>
	Tetromino TakeFromTetrominoQueue();

	/// <summary>
	/// Debug function to force the next piece type.
	/// </summary>
	/// <param name="_debugTetType">Chosen tetromino type.</param>
	/// <returns>Debug type.</returns>
	Tetromino TakeFromTetrominoQueue(Tetromino _debugTetType);

	/// <summary>
	/// Complementary function to process input movement when the game status allows it.
	/// </summary>
	/// <param name="_nextAction">User input.</param>
	/// <param name="_print">Print debug lines for testing purposes.</param>
	void ProcessMovement(KeyBind _nextAction, bool _print=false);

	/// <summary>
	/// Allocates memory for the game board.
	/// </summary>
	/// <param name="_print">Print debug lines for testing purposes.</param>
	void PrepareBoard(bool _print = false);

	/// <summary>
	/// Updates game board variable.
	/// </summary>
	void UpdateBoard(bool _clear = false);

	/// <summary>
	/// Moves active piece down.
	/// </summary>
	void MoveDown();

	/// <summary>
	/// Moves active piece left.
	/// </summary>
	void MoveLeft();

	/// <summary>
	/// Moves active piece right.
	/// </summary>
	void MoveRight();

	/// <summary>
	/// Validates the piece movement, given the action performed. This function prevents: Pieces going through border, other pieces or floor.
	/// </summary>
	bool ValidateMove(KeyBind _action);

	void Land();

	void PlaceBlocks();

#pragma endregion

public:

#pragma region Public methods
	/// <summary>
	/// Print the whole game board.
	/// </summary>
	void PrintBoard();

	/// <summary>
	/// Function is the main entry point of user input and game management that instructs the program what to do over time.
	/// </summary>
	/// <param name="_nextAction">The input that will be processed. This is definitive.</param>
	/// <param name="_print">Print debug lines for testing purposes.</param>
	void Update(KeyBind _nextAction, bool _print=false);

	/// <summary>
	/// Function to start the game in the standard way. No debugs or test prints: Official game start.
	/// </summary>
	void StartGame();
#pragma endregion

	/// <summary>
	/// Constructor for menu-based parameters.
	/// </summary>
	/// <param name="_gameSpeed">stands for game speed in milisseconds (ms).</param>
	Game(int _gameSpeed, bool _doubleBag, bool _print = false);

	/// <summary>
	/// Constructor for the defaut parameters taken from the configuration files (.cfg).
	/// </summary>
	Game(bool _double_bag, bool _print = false);

	/// <summary>
	/// Generic Class Destructor.
	/// </summary>
	~Game();

};