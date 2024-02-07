#pragma once

#include <Piece.h>

/// <summary>
/// Enumerator to process key mapping against the application.
/// </summary>
typedef enum KeyBind {
//?	UP,
	DOWN,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	IDLE //Special action for when an user doesn't press any key at a given time interval.
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
	Piece::Tetromino value;
	TetrominoNode* next;
} TetrominoNode;

/// <summary>
/// Enumerator to help describing the current game status.
/// </summary>
typedef enum GameStatus {
	START, // The game just started.
	MOVE,  // A tetromino move is being performed.
	LAND,  // Current tetromino has reached the final spot.
	OVER   // Conditions for game over are met.
} GameStatus;

/// <summary>
/// Class for game logic.
/// In game memory and steps validation.
/// Each instance is a round of a game.
/// </summary>
class Game {
protected:
	//? vector<Piece> _piece;
	Piece::Tetromino * _tetrominoQueueLL;
	
	/// <summary>
	/// Function that generates the starting pieces.
	/// </summary>
	/// <param name="_double_bag">true: Use double bag randomization. false: Use single bag randomization.</param>
	/// <param name="_print">(Optional) Printing debug for testing purposes.</param>
	void GenerateRandomTetrominoQueue(bool _double_bag, bool _print = false);

	/// <summary>
	/// Takes the first piece from the queue and inserts one more at the last.
	/// </summary>
	/// <returns>The removed tetromino type enumerator.</returns>
	Piece::Tetromino TakeFromTetrominoQueue();

public:
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
	/// Function is the main entry point of user input and game management that instructs the program what to do over time.
	/// </summary>
	/// <param name="nextAction">The input that will be processed. This is definitive.</param>
	void Update(KeyBind nextAction);

	/// <summary>
	/// Function to start the game in the standard way. No debugs or test prints: Official game start.
	/// </summary>
	void StartGame();
};