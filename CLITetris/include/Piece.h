#pragma once

#include <CLITetris.h>

#pragma region Auxiliary structures outside class definition
/// <summary>
/// Enumerating tetromino type codes to instance the piece.
/// </summary>
typedef enum Tetromino {
	O,
	L,
	J,
	I,
	T,
	S,
	Z
} Tetromino;

/// <summary>
/// Bidimensional coordinate structure. Each piece has 4.
/// </summary>
typedef struct Block {
	int x;
	int y;
	Block(int a, int b) : x(a), y(b) {}
} Block;

/// <summary>
/// Simple enumerator to simplify rotation input.
/// </summary>
typedef enum PieceBlockRotation {
	LEFT,
	RIGHT
} PieceBlockRotation;
#pragma endregion

class Piece {

public:

#pragma region Properties

	/// <summary>
	/// If piece is "O", rotation must be prohibited by the object.
	/// </summary>
	bool DISABLE_ROTATION = false;

	/// <summary>
	/// Property tetromino type.
	/// </summary>
	Tetromino tetromino;

	/// <summary>
	/// Returns pointer to allocated coordinates from this piece.
	/// </summary>
	Block* _blocks = NULL;
#pragma endregion

	/// <summary>
	/// Default constructor. Tetromino required for instancing.
	/// </summary>
	/// <param name="_tetromino">: The desired tetromino type.</param>
	Piece(Tetromino _tetromino);

protected:

	/// <summary>
	/// Accesses memory to allocate the memory addresses and sets the coordinates for each piece block.
	/// </summary>
	/// <param name="tetromino">: The desired tetromino type.</param>
	/// <returns>A pointer to the allocated memory.</returns>
	Block* AllocatePiece(Tetromino tetromino);
};