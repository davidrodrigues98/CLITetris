#pragma once

#include <CLITetris.h>


class Piece {

public:
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
	/// Simple enumerator to simplify rotation input.
	/// </summary>
	typedef enum PieceBlockRotation {
		LEFT,
		RIGHT
	} PieceBlockRotation;

	/// <summary>
	/// Default constructor. Tetromino required for instancing.
	/// </summary>
	/// <param name="_tetromino">: The desired tetromino type.</param>
	Piece(Tetromino __tetromino);

	/// <summary>
	/// Bidimensional coordinate structure. Each piece has 4.
	/// </summary>
	typedef struct Block {
		int x = -1;
		int y = -1;
	} Block;

	/// <summary>
	/// Returns pointer to allocated coordinates from this piece.
	/// </summary>
	Block *GetPiece();

	/// <summary>
	/// Algorithm to rotate the selected tetromino piece in a given direction.
	/// </summary>
	/// <param name="_direction">Input direction: LEFT or RIGHT.</param>
	void Rotate(PieceBlockRotation _direction);

	
protected:
	/// <summary>
	/// Accesses memory to allocate the memory addresses and sets the coordinates for each piece block.
	/// </summary>
	/// <param name="tetromino">: The desired tetromino type.</param>
	/// <returns>A pointer to the allocated memory.</returns>
	Block* AllocatePiece(Piece::Tetromino tetromino);

	Block *_blocks = NULL;
	Tetromino _tetromino;
};