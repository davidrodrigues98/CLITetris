#pragma once

#include "CLITetris.h"

class Piece {


public:
	typedef enum Shape {
		SQUARE,
		L,
		RECTANGLE,
		PYRAMID
	} Shape;

	Piece(Shape _shape) {
		switch (_shape) {

			default:throw;
		}
	}

	typedef struct Block {
		int x = -1;
		int y = -1;
	} Block;

	Block *GetPiece;

	void Rotate(int _degrees);

protected:
	Block *piece;
};