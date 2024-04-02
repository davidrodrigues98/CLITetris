#include <Piece.h>

Block* Piece::AllocatePiece(Tetromino tetromino) {
	// Allocating 4 memory addresses with the size of a block.
	Block* array = (Block*)malloc(4 * sizeof(Block));

	// { x, y }
	switch (tetromino) {
	case Tetromino::O:
		array[0] = { 0, 0 };
		array[1] = { 1, 0 };
		array[2] = { 0, 1 };
		array[3] = { 1, 1 };
		break;
	case Tetromino::I:
		array[0] = { 0, 0 };
		array[1] = { 1, 0 };
		array[2] = { 2, 0 };
		array[3] = { 3, 0 };
		break;
	case Tetromino::L:
		array[0] = { 0, 1 };
		array[1] = { 1, 1 };
		array[2] = { 2, 1 };
		array[3] = { 2, 0 };
		break;
	case Tetromino::J:
		array[0] = { 2, 1 };
		array[1] = { 1, 1 };
		array[2] = { 0, 1 };
		array[3] = { 0, 0 };
		break;
	case Tetromino::T:
		array[0] = { 0, 1 };
		array[1] = { 1, 1 };
		array[2] = { 1, 0 };
		array[3] = { 2, 1 };
		break;
	case Tetromino::S:
		array[0] = { 0, 1 };
		array[1] = { 1, 1 };
		array[2] = { 1, 0 };
		array[3] = { 2, 0 };
		break;
	case Tetromino::Z:
		array[0] = { 0, 0 };
		array[1] = { 1, 0 };
		array[2] = { 1, 1 };
		array[3] = { 2, 1 };
		break;
	default:
		throw std::invalid_argument("Invalid enumerator argument given when creating a new Piece instance.");
		break;
	}

	return array;
}

Piece::Piece(Tetromino _tetromino) {
	this->tetromino = _tetromino;
	// Starting relative allocation.
	_blocks = Piece::AllocatePiece(_tetromino);
	// Sync with board (center)
	int centerX = gBoardRules.gameWidth / 2;
	for (int i = 0; i < 4; i++) {

		(_blocks + i)->x += centerX + 1;
	}
}