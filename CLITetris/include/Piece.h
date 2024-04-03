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

/// <summary>
/// Structure designed to represent doubly linked list to store tetromino rotation relative coordinates. 
/// </summary>
typedef struct TetrominoRotateNode {
	TetrominoRotateNode* prev;
	TetrominoRotateNode* next;
	Block* relativeCoordinatesPrev; //max +3
	Block* relativeCoordinatesNext; //max +3
} TetrominoRotateNode;
#pragma endregion

class Piece {

public:

#pragma region Properties

	/// <summary>
	/// If piece is "O", rotation must be prohibited by the object.
	/// </summary>
	bool DISABLE_ROTATION = false;

	// Doubly linked list pointers for the rotation mask:
	TetrominoRotateNode* gRotateHead = nullptr, * gRotateTail = nullptr, * gRotateCurrent = nullptr;

	/// <summary>
	/// Property tetromino type.
	/// </summary>
	Tetromino tetromino;

	/// <summary>
	/// Returns pointer to allocated coordinates from this piece.
	/// </summary>
	Block* _blocks = nullptr;
#pragma endregion

	/// <summary>
	/// Default constructor. Tetromino required for instancing.
	/// </summary>
	/// <param name="_tetromino">: The desired tetromino type.</param>
	Piece(Tetromino _tetromino);

	/// <summary>
	/// Generic Piece class destructor.
	/// </summary>
	~Piece();

	/// <summary>
	/// Effectively inserts nodes with relative position values for next or previous piece rotation coordinates (2D).
	/// </summary>
	/// <param name="_r0p">rotation 0 previous</param>
	/// <param name="_r0n">rotation 0 next</param>
	/// <param name="_r1p">rotation 1 previous</param>
	/// <param name="_r1n">rotation 1 next</param>
	/// <param name="_r2p">rotation 2 previous</param>
	/// <param name="_r2n">rotation 2 next</param>
	/// <param name="_r3p">rotation 3 previous</param>
	/// <param name="_r3n">rotation 3 next</param>
	void CreateDoublyLinkedListPointer(
		Block* _r0p,
		Block* _r0n,
		Block* _r1p,
		Block* _r1n,
		Block* _r2p,
		Block* _r2n,
		Block* _r3p,
		Block* _r3n
	);

	/// <summary>
	/// Shortened version of "CreateDoublyLinkedListPointer" function, but only allows 2 rotations. Some pieces only use 2 rotations.
	/// </summary>
	/// <param name="_r0">rotation 0</param>
	/// <param name="_r1">rotation 1</param>
	void Short_CreateDoublyLinkedListPointer(
		Block* _r0,
		Block* _r1
	);

	/// <summary>
	/// Auxiliary function to help load rotation masks into the doubly linked list.
	/// </summary>
	void CreateRotateMaskForTetromino();

	/// <summary>
	/// Navigates throughout the doubly linked list for the relative rotation mask. 
	/// </summary>
	/// <param name="_direction">Which direction to navigate (rotate).</param>
	/// <param name="_print">Enable/disable debug mode.</param>
	void RotatePiece(PieceBlockRotation _direction, bool _print = false);

protected:

	/// <summary>
	/// Accesses memory to allocate the memory addresses and sets the coordinates for each piece block.
	/// </summary>
	/// <param name="tetromino">: The desired tetromino type.</param>
	/// <returns>A pointer to the allocated memory.</returns>
	Block* AllocatePiece(Tetromino tetromino);
};