#pragma once

#include <Piece.h>
#include <Printer.h>

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
/// Structure designed to represent doubly linked list to store tetromino rotation relative coordinates. 
/// </summary>
typedef struct TetrominoRotateNode {
	TetrominoRotateNode* prev;
	TetrominoRotateNode* next;
	Piece::Block *relativeCoordinatesPrev; //max +3
	Piece::Block* relativeCoordinatesNext; //max +3
} TetrominoRotateNode;

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
	/// <summary>
	/// Size of each board line.
	/// </summary>
	int _lineSize;

	Printer::Visuals* _gameBoard;

	BoardRules _boardRules;
	
	Piece::Tetromino *_tetrominoQueueLL;
	//? TetrominoRotateNode* _tetrominoRotateMask;
	
	/// <summary>
	/// Pointer reference to the piece being controlled at the moment.
	/// </summary>
	Piece* _activePiece;

	
	/// <summary>
	/// Function that generates the starting pieces.
	/// </summary>
	/// <param name="_double_bag">true: Use double bag randomization. false: Use single bag randomization.</param>
	/// <param name="_print">(Optional) Printing debug for testing purposes.</param>
	void GenerateRandomTetrominoQueue(bool _double_bag, bool _print = false);

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

	void RotatePiece(Piece::PieceBlockRotation _direction);

	/* //?
	/// <summary>
	/// Auxiliary function to help load rotation masks into the main map.
	/// </summary>
	/// <param name="_tetromino">Selected tetromino.</param>
	/// <returns>Map with the possible rotate positions to be inserted into the main map.</returns>
	TetrominoRotateNode* CreateRotateMaskForTetromino(Piece::Tetromino _tetromino);
	*/
public:
	/// <summary>
	/// Print the whole game board.
	/// </summary>
	void PrintBoard();

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
	/// <param name="_nextAction">The input that will be processed. This is definitive.</param>
	/// <param name="_print">Print debug lines for testing purposes.</param>
	void Update(KeyBind _nextAction, bool _print=false);

	/// <summary>
	/// Function to start the game in the standard way. No debugs or test prints: Official game start.
	/// </summary>
	void StartGame();


};