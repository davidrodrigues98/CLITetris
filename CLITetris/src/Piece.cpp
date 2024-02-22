#include <Piece.h>

Piece::Block* Piece::AllocatePiece(Piece::Tetromino tetromino) {
	// Allocating 4 memory addresses with the size of a block.
	Piece::Block *array = (Piece::Block*)malloc(4 * sizeof(Piece::Block));

#pragma region Tetromino coordinates assignment
	switch (tetromino) {
	case Piece::Tetromino::O:
		array[0].x = 0;
		array[0].y = 0;
		array[1].x = 1;
		array[1].y = 0;
		array[2].x = 0;
		array[2].y = 1;
		array[3].x = 1;
		array[3].y = 1;
		break;
	case Piece::Tetromino::I:
		array[0].x = 0;
		array[0].y = 0;
		array[1].x = 1;
		array[1].y = 0;
		array[2].x = 2;
		array[2].y = 0;
		array[3].x = 3;
		array[3].y = 0;
		break;
	case Piece::Tetromino::L:
		array[0].x = 0;
		array[0].y = 1;
		array[1].x = 1;
		array[1].y = 1;
		array[2].x = 2;
		array[2].y = 1;
		array[3].x = 2;
		array[3].y = 0;
		break;
	case Piece::Tetromino::J:
		array[0].x = 0;
		array[0].y = 0;
		array[1].x = 0;
		array[1].y = 1;
		array[2].x = 1;
		array[2].y = 1;
		array[3].x = 2;
		array[3].y = 1;
		break;
	case Piece::Tetromino::T:
		array[0].x = 1;
		array[0].y = 0;
		array[1].x = 0;
		array[1].y = 1;
		array[2].x = 1;
		array[2].y = 1;
		array[3].x = 2;
		array[3].y = 1;
		break;
	case Piece::Tetromino::S:
		array[0].x = 0;
		array[0].y = 1;
		array[1].x = 1;
		array[1].y = 1;
		array[2].x = 1;
		array[2].y = 0;
		array[3].x = 2;
		array[3].y = 0;
		break;
	case Piece::Tetromino::Z:
		array[0].x = 0;
		array[0].y = 0;
		array[1].x = 1;
		array[1].y = 0;
		array[2].x = 1;
		array[2].y = 1;
		array[3].x = 2;
		array[3].y = 1;
		break;
	default:
		throw std::invalid_argument("Invalid enumerator argument given when creating a new Piece instance.");
		break;
	}
#pragma endregion

	return array;
}

Piece::Piece(Piece::Tetromino _tetromino) {
	this->tetromino = _tetromino;
	// Starting relative allocation.
	_blocks = Piece::AllocatePiece(_tetromino);
	// Sync with board (center)
	int centerX = gBoardRules.gameWidth / 2;
	for (int i = 0; i < 4; i++) {
		
		(_blocks + i)->x += centerX + 1;
	}	
}