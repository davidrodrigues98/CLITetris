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

void Piece::CreateDoublyLinkedListPointer(
	Block* _r0p,
	Block* _r0n,
	Block* _r1p,
	Block* _r1n,
	Block* _r2p,
	Block* _r2n,
	Block* _r3p,
	Block* _r3n
)
{
	//r0 Original Position
	gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	gRotateTail->relativeCoordinatesPrev = _r0p;
	gRotateTail->relativeCoordinatesNext = _r0n;


	//r1
	TetrominoRotateNode* aux = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	aux->relativeCoordinatesPrev = _r1p;
	aux->relativeCoordinatesNext = _r1n;
	gRotateTail->next = aux;
	aux->prev = gRotateTail;
	TetrominoRotateNode* aux2 = aux;
	aux = aux->next;

	//r2
	aux = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	aux->relativeCoordinatesPrev = _r2p;
	aux->relativeCoordinatesNext = _r2n;
	aux->prev = aux2;
	aux2->next = aux;

	//r3
	gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	gRotateHead->relativeCoordinatesPrev = _r3p;
	gRotateHead->relativeCoordinatesNext = _r3n;
	aux->next = gRotateHead;
	gRotateTail->prev = gRotateHead;
	gRotateHead->prev = aux;
	gRotateHead->next = gRotateTail;

	gRotateCurrent = gRotateTail;
}

void Piece::Short_CreateDoublyLinkedListPointer(
	Block* _r0,
	Block* _r1
)
{
	// r1
	gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	gRotateTail->relativeCoordinatesPrev = _r1;
	gRotateTail->relativeCoordinatesNext = _r1;


	// r0 Original position.
	gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
	gRotateHead->relativeCoordinatesPrev = _r0;
	gRotateHead->relativeCoordinatesNext = _r0;
	gRotateTail->next = gRotateHead;
	gRotateTail->prev = gRotateHead;
	gRotateHead->next = gRotateTail;
	gRotateHead->prev = gRotateTail;
	gRotateCurrent = gRotateHead;
}

void Piece::CreateRotateMaskForTetromino() {
    Block* r0p, * r0n, * r1p, * r1n, * r2p, * r2n, * r3p, * r3n;
    switch (tetromino)
    {
    case L: {

        r0p = new Block[4]
        {
            { 0, 2 }, { 1, 1 }, { 2, 0 }, { 1, -1 }
        };
        r0n = new Block[4]
        {
            { -1, 0 }, { 0, 1 }, { 1, 2 }, { 2, 1 }
        };
        r1p = new Block[4]
        {
            { -2, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 }
        };
        r1n = new Block[4]
        {
            { 0, -2 }, { -1, -1 }, { -2, 0 }, { -1, 1 }
        };
        r2p = new Block[4]
        {
            { 1, -1 }, { 0, 0 }, { -1, 1 }, { 0, 2 }
        };
        r2n = new Block[4]
        {
            { 2, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
        };
        r3p = new Block[4]
        {
            { 1, 0 }, { 0, -1 }, { -1, -2 }, { -2, -1 }
        };
        r3n = new Block[4]
        {
            { -1, 1 }, { 0, 0 }, { 1, -1 }, { 0, -2 }
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case J: {
        r0p = new Block[4]
        {
            { 2, 0 }, { 1, 1 }, { 0, 2 }, { -1, 1 }
        };
        r0n = new Block[4]
        {
            { 1, 2 }, { 0, 1 }, { -1, 0 }, { 0, -1 }
        };
        r1p = new Block[4]
        {
            { 0, 1 }, { -1, 0 }, { -2, -1 }, { -1, -2 }
        };
        r1n = new Block[4]
        {
            { -2, 0 }, { -1, -1 }, { 0, -2 }, { 1, -1 }
        };
        r2p = new Block[4]
        {
            { -1, 1 }, { 0, 0 }, { 1, -1 }, { 2, 0 }
        };
        r2n = new Block[4]
        {
            { 0, -1 }, { 1, 0 }, { 2, 1 }, { 1, 2 }
        };
        r3p = new Block[4]
        {
            { -1, -2 }, { 0, -1 }, { 1, 0 }, { 0, 1 }
        };
        r3n = new Block[4]
        {
            { 1, -1 }, { 0, 0 }, { -1, 1 }, { -2, 0 }
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case I: {
        r0n = new Block[4]{
            { 0, 0 }, { 1, -1 }, { 2, -2 }, { 3, -3 }
        };
        r1n = new Block[4]{
            { 0, 0 }, { -1, 1 }, { -2, 2 }, { -3, 3 }
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    case T: {
        r0p = new Block[4]
        {
            { 0, 1 }, { 1, 0 }, { 0, -1 }, { 2, -1 }
        };
        r0n = new Block[4]
        {
            { -1, 1 }, { 0, 0 }, { 1, -1 }, { 1, -1 }
        };
        r1p = new Block[4]
        {
            { 0, 0 }, { -1, 1 }, { 0, 0 }, { -2, 2 }
        };
        r1n = new Block[4]
        {
            { 0, -1 }, { -1, 0 }, { 0, 1 }, { -2, 1 }
        };
        r2p = new Block[4]
        {
            { -1, 0 }, { 0, -1 }, { 1, 0 }, { 1, -2 }
        };
        r2n = new Block[4]
        {
            { 0, 0 }, { 1, -1 }, { 0, 0 }, { 2, -2 }
        };
        r3p = new Block[4]
        {
            { 1, -1 }, { 0, 0 }, { -1, 1 }, { -1, 1 }
        };
        r3n = new Block[4]
        {
            { 1, 0 }, { 0, 1 }, { -1, 0 }, { -1, 2 }
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case S: {
        r0n = new Block[4]{
            {0,1},{1,0},{0,-1},{1,-2}
        };
        r1n = new Block[4]{
            {0,-1},{-1,0},{0,1},{-1,2}
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    case Z: {
        r0n = new Block[4]
        {
            {-1,0},{0,-1},{1,0},{2,-1}
        };
        r1n = new Block[4]
        {
            {1,0},{0,1},{-1,0},{-2,1}
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    default:
        throw std::invalid_argument("Invalid enumerator argument given when creating a new Piece instance.");
        break;

    }
}

void Piece::RotatePiece(PieceBlockRotation _direction, bool _print) {
    if (DISABLE_ROTATION == false) {
        if (_direction == PieceBlockRotation::RIGHT)
        {
            gRotateCurrent = gRotateCurrent->next;
            for (int i = 0; i < 4; i++) {
                Block* blocks = _blocks;
                Block* relative = gRotateCurrent->relativeCoordinatesNext;
                Block* relativeI = relative + i;
                (blocks + i)->x += (relativeI)->x;
                (blocks + i)->y += (relativeI)->y;
            }
        }
        else {
            gRotateCurrent = gRotateCurrent->prev;
            for (int i = 0; i < 4; i++) {
                Block* blocks = _blocks;
                Block* relative = gRotateCurrent->relativeCoordinatesPrev;
                Block* relativeI = relative + i;
                (blocks + i)->x += (relativeI)->x;
                (blocks + i)->y += (relativeI)->y;
            }
        }
    }
    else
        if (_print)
            wprintf(L"Debug: Game::RotatePiece -> DISABLE_ROTATION flag was \"true\". Rotation was not allowed.");

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
    // Create rotation mask.
    if (_tetromino != O)
        CreateRotateMaskForTetromino();
    else
        DISABLE_ROTATION = true;
}

Piece::~Piece() {
    free(_blocks);   // Clear memory for block coordinates.

    _blocks = nullptr;
    gRotateCurrent = nullptr;
    gRotateTail = nullptr;
    //this is totally NOT ok
    TetrominoRotateNode* tmp = gRotateHead;
    while (gRotateHead->next->next != nullptr) {            // Clear memory for rotation mask doubly linked list.
        tmp = tmp->next;                      // Needed to "delete[]" the Blocks because the "new" operator was used.
        gRotateHead = gRotateHead->next;        // Then, use "free" for the whole node address.
        free(tmp->relativeCoordinatesNext);
        tmp->relativeCoordinatesNext = nullptr;
        free(tmp->relativeCoordinatesPrev);
        tmp->relativeCoordinatesPrev = nullptr;
        free(tmp);

    }
}