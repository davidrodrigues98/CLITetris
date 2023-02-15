#pragma once

#include <Piece.h>

/// <summary>
/// Structure to handle linked list queue management.
/// </summary>
typedef struct TetrominoNode {
	// Tetromino value.
	Piece::Tetromino value;
	TetrominoNode* next;
} TetrominoNode;

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
	/// <param name="_officialRules">(Optional) Printing debug for testing purposes.</param>
	void GenerateRandomTetrominoQueue(bool _print = false);

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
	Game(int _gameSpeed, bool print);

	/// <summary>
	/// Constructor for the defaut parameters taken from the configuration files (.cfg).
	/// </summary>
	Game(bool print = false);
};