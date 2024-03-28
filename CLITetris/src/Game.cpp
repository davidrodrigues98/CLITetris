#include <Game.h>
using namespace std;

GameStatus gGameStatus;

void Game::CreateDoublyLinkedListPointer(
    Piece::Block *_r0p,
    Piece::Block *_r0n,
    Piece::Block *_r1p,
    Piece::Block *_r1n,
    Piece::Block *_r2p,
    Piece::Block *_r2n,
    Piece::Block *_r3p,
    Piece::Block *_r3n
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

void Game::Short_CreateDoublyLinkedListPointer(
    Piece::Block* _r0,
    Piece::Block* _r1
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

void Game::CreateRotateMaskForTetromino(Piece::Tetromino _tetromino) {
    Piece::Block* r0p, * r0n, * r1p, * r1n, * r2p, * r2n, * r3p, * r3n;
    switch (_tetromino)
    {
    case Piece::L: {
        
        r0p = new Piece::Block[4]
        {
            { -1, 0 }, { 0,1 }, { 1,2 }, { 2,1 }
        };
        r0n = new Piece::Block[4]
        {
            { 0, -2 }, { -1, -1 }, { -2, 0 }, { -1, 1 }
        };
        r1p = new Piece::Block[4]
        {
            {-2,-1},{-1,0},{0,1},{1,0}
        };
        r1n = new Piece::Block[4]
        {
            {0,-2},{-1,-1},{-2,0},{-1,1}
        };
        r2p = new Piece::Block[4]
        {
            {1,-1},{0,0},{-1,1},{0,2}
        };
        r2n = new Piece::Block[4]
        {
            {2,1},{1,0},{0,-1},{-1,0}
        };
        r3p = new Piece::Block[4]
        {
            {1,0},{0,-1},{-1,-2},{-2,-1}
        };
        r3n = new Piece::Block[4]
        {
            {1,1},{0,0},{1,-1},{0,-2}
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case Piece::J: {
        r0p = new Piece::Block[4]
        {
            { 1, 2 }, { 0,1 }, { -1,0 }, { 0,-1 }
        };
        r0n = new Piece::Block[4]
        {
            {0,0},{1,1},{0,2},{-1,1}
        };
        r1p = new Piece::Block[4]
        {
            {-2,0},{-1,-1},{0,-2},{1,-1}
        };
        r1n = new Piece::Block[4]
        {
            {0,1},{-1,0},{1,0},{2,1}
        };
        r2p = new Piece::Block[4]
        {
            {0,-1},{1,0},{2,1},{1,2}
        };
        r2n = new Piece::Block[4]
        {
            {-1,1},{0,0},{1,-1},{2,0}
        };
        r3p = new Piece::Block[4]
        {
            {1,-1},{0,0},{-1,1},{-2,0}
        };
        r3n = new Piece::Block[4]
        {
            {-1,-2},{0,-1},{0,-1},{1,-2}
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case Piece::I: {
        r0n = new Piece::Block[4] {
            {0,0},{1,-1},{2,-2},{3,-3}
        };
        r1n = new Piece::Block[4] {
            {0,0},{-1,1},{-2,2},{-3,3}
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    case Piece::T: {
        r0p = new Piece::Block[4]
        {
            {-1, 1}, {0,0}, {1,-1}, {1,-1}
        };
        r0n = new Piece::Block[4]
        {
            {0, 1}, {1, 0}, {0, -1}, {2, -1}
        };
        r1p = new Piece::Block[4]
        {
            {0, -1}, {1, 0}, {0, 1}, {2, 1}
        };
        r1n = new Piece::Block[4]
        {
            {0, 0}, {-1, 1}, {0, 0}, {-2, 2}
        };
        r2p = new Piece::Block[4]
        {
            {0, -1}, {1, -1}, {0, 0}, {2, -2}
        };
        r2n = new Piece::Block[4]
        {
            {-1, 0}, {0, -1}, {1, 0}, {1, -2}
        };
        r3p = new Piece::Block[4]
        {
            {1, 0}, {0, 1}, {-1, 0}, {-1, 2}
        };
        r3n = new Piece::Block[4]
        {
            {1, -1}, {0, 0}, {-1, 1}, {-1, 1}
        };
        CreateDoublyLinkedListPointer(r0p, r0n, r1p, r1n, r2p, r2n, r3p, r3n);
        break;
    }
    case Piece::S: {
        r0n = new Piece::Block[4] {
            {0,1},{1,0},{0,-1},{1,-2}
        };
        r1n = new Piece::Block[4] {
            {0,-1},{-1,0},{0,1},{-1,2}
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    case Piece::Z: {
        r0n = new Piece::Block[4]
        {
            {-1,0},{0,-1},{1,0},{2,-1}
        };
        r1n = new Piece::Block[4]
        {
            {1,0},{0,1},{-1,0},{-2,1}
        };
        Short_CreateDoublyLinkedListPointer(r0n, r1n);
        break;
    }
    case Piece::O: { // Special case, loop into same node with empty value to still validate the rotation for a square.
        /*gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block dummyR[4] = {
            {0,0},{0,0},{0,0},{0,0}
        };
        gRotateHead->relativeCoordinatesNext = dummyR;
        gRotateHead->relativeCoordinatesPrev = dummyR;
        gRotateTail = gRotateHead;
        gRotateHead->prev = gRotateHead;
        gRotateHead->next = gRotateHead;
        gRotateCurrent = gRotateHead;
        break;
        */
        throw std::invalid_argument("Invalid enumerator argument given when creating a new Piece instance.");
    }
    default:
        throw std::invalid_argument("Invalid enumerator argument given when creating a new Piece instance.");
        break;

    }
}



void Game::RotatePiece(Piece::PieceBlockRotation _direction) {
    if (_direction == Piece::PieceBlockRotation::RIGHT)
    {
        gRotateCurrent = gRotateCurrent->next;
        for (int i = 0; i < 4; i++) {
            Piece::Block* blocks = _activePiece->_blocks;
            Piece::Block* relative = gRotateCurrent->relativeCoordinatesNext;
            (blocks + i)->x += (relative + i)->x;
            (blocks + i)->y += (relative + i)->y;
        }
    }
    else {
        gRotateCurrent = gRotateCurrent->prev;
        for (int i = 0; i < 4; i++) {
            Piece::Block* blocks = _activePiece->_blocks; 
            Piece::Block* relative = gRotateCurrent->relativeCoordinatesPrev;
            (blocks + i)->x += (relative + i)->x;
            (blocks + i)->y += (relative + i)->y;
        }
    }
}

KeyBind KeyEventProc(KEY_EVENT_RECORD ker)
{
    WORD recordedKeyCode = ker.wVirtualKeyCode;
    KeyBind result = IDLE;

    // Virtual key mapping.
    switch (recordedKeyCode)
    {
        case 37: result = LEFT;         break;
        case 38: result = ROTATE_RIGHT; break;
        case 39: result = RIGHT;        break;
        //? case 40: result = DOWN; break;
        default: result = IDLE;         break;
    }

    return result;
}

Game::Game(bool _doubleBag, bool _print) {
    Game::GenerateRandomTetrominoQueue(_doubleBag, _print);
    // Setting new game status.
    gGameStatus = START;
    // Calc size of each line.
    _lineSize = gBoardRules.gameWidth;

    //Make a dynamic rotate mask load.

}

void Game::GenerateRandomTetrominoQueue(bool _double_bag, bool _print) {
    // Fixed array to support the starting randomization.
    Piece::Tetromino shuffleData[TETRO_QUEUE_SIZE] = {
        Piece::Tetromino::O,
        Piece::Tetromino::L,
        Piece::Tetromino::J,
        Piece::Tetromino::I,
        Piece::Tetromino::T,
        Piece::Tetromino::S,
        Piece::Tetromino::Z
    };

    // Calling the shuffle function here:
    // To obtain a time-based seed.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // Only use 1 bag with 7 distinct tetromino.
    if (_double_bag == false) {
        // Shuffling our array
        shuffle(shuffleData, shuffleData + TETRO_QUEUE_SIZE, default_random_engine(seed));

        // Printing array (for debug testing).
        if (_print) {
            for (int i = 0; i < TETRO_QUEUE_SIZE; i++)
                wprintf(L"%i ", shuffleData[i]);
            wprintf(L"\n");
        }

        // Creating linked list based on the randomized array.
        TetrominoNode* fill_ptr = (TetrominoNode*)malloc(sizeof(TetrominoNode));
        fill_ptr->value = shuffleData[0];
        fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
        gQueueHead = fill_ptr;
        fill_ptr = fill_ptr->next;

        for (int i = 1; i < TETRO_QUEUE_SIZE; i++)
        {
            fill_ptr->value = shuffleData[i];
            fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
            gQueueTail = fill_ptr;
            fill_ptr = fill_ptr->next;
        }

        gQueueTail->next = gQueueHead;
        gQueueCurrent = gQueueHead;
    }
    // Use 2 bags with 7 distinct tetromino in each.
    else {
        // Copy of support array for the starting randomization.
        Piece::Tetromino shuffleData2[TETRO_QUEUE_SIZE] = {
            Piece::Tetromino::O,
            Piece::Tetromino::L,
            Piece::Tetromino::J,
            Piece::Tetromino::I,
            Piece::Tetromino::T,
            Piece::Tetromino::S,
            Piece::Tetromino::Z
        };

        // Shuffling both arrays.
        shuffle(shuffleData, shuffleData + TETRO_QUEUE_SIZE,
            default_random_engine(seed));

        // Reloading seed to get a different combination on the second one.
        seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle(shuffleData2, shuffleData2 + TETRO_QUEUE_SIZE,
            default_random_engine(seed));

        // Printing array (for debug testing).
        if (_print) {
            for (int i = 0; i < TETRO_QUEUE_SIZE; i++)
                wprintf(L"%i ", shuffleData[i]);
            for (int i = 0; i < TETRO_QUEUE_SIZE; i++)
                wprintf(L"%i ", shuffleData2[i]);
            wprintf(L"\n");
        }

        // Creating linked list based on the randomized array.
        TetrominoNode* fill_ptr = (TetrominoNode*)malloc(sizeof(TetrominoNode));
        fill_ptr->value = shuffleData[0];
        fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
        gQueueHead = fill_ptr;
        fill_ptr = fill_ptr->next;
        for (int i = 1; i < TETRO_QUEUE_SIZE; i++)
        {
            fill_ptr->value = shuffleData[i];
            fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
            gQueueTail = fill_ptr;
            fill_ptr = fill_ptr->next;
        }
        for (int i = 0; i < TETRO_QUEUE_SIZE; i++)
        {
            fill_ptr->value = shuffleData2[i];
            fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
            gQueueTail = fill_ptr;
            fill_ptr = fill_ptr->next;
        }
        gQueueTail->next = gQueueHead;
        gQueueCurrent = gQueueHead;
    }
}

Piece::Tetromino Game::TakeFromTetrominoQueue() {
    Piece::Tetromino result = gQueueCurrent->value;
    gQueueCurrent = gQueueCurrent->next;
    return result;
}

void Game::Update(KeyBind _nextAction, bool _print) {
    switch (gGameStatus) {
        case GameStatus::START: 
            _activePiece = new Piece(TakeFromTetrominoQueue());
            CreateRotateMaskForTetromino(_activePiece->tetromino);
            if(_print) 
                wprintf(L"%i\n", _activePiece->tetromino);
            gGameStatus = GameStatus::MOVE;
            break;
        case GameStatus::MOVE:
            UpdateBoard(true);
            ProcessMovement(_nextAction, _print);
            break;
    }
    UpdateBoard();
}

void Game::ProcessMovement(KeyBind _nextAction, bool _print) {
    switch (_nextAction) {
        case KeyBind::DOWN: 
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"DOWN\n");
                MoveDown();
            }
            break;
        case KeyBind::LEFT:
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"LEFT\n");
                MoveLeft();
            }
            break;
        case KeyBind::RIGHT:
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"RIGHT\n");
                MoveRight();
            }
            break;
        case KeyBind::ROTATE_LEFT: break;
        case KeyBind::ROTATE_RIGHT: 
            RotatePiece(Piece::PieceBlockRotation::RIGHT);
            break;
    }
}

bool Game::ValidateMove(KeyBind _action) {
    Piece::Block* blocks = _activePiece->_blocks;
    int nX = 0, nY = 0;
    switch (_action) {
        case KeyBind::LEFT:
            nX = -1;
        break;
        case KeyBind::RIGHT:
            nX = 1;
        break;
        case KeyBind::DOWN:
            nY = 1;
        default:break;
    }
    for (int i = 0; i < 4; i++) {
        int x = (blocks + i)->x;
        int y = (blocks + i)->y;

        // Condition logic: Visual enumerator >10 means that it is a border.
        Printer::Visuals cell = _gameBoard[_lineSize + _lineSize * (y + nY) + x + nX];
        if (cell >= 10)
            return false;
    }
    return true;
}

void Game::MoveDown() {
    Piece::Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->y++;
    }
}

void Game::MoveLeft() {
    Piece::Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->x--;
    }
}

void Game::MoveRight() {
    Piece::Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->x++;
    }
}

void Game::StartGame() {
    PrepareBoard();
    gGameStatus = GameStatus::START;
}

void Game::UpdateBoard(bool _clear) {
    Piece::Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        int x = (blocks+i)->x;
        int y = (blocks+i)->y;
        _gameBoard[_lineSize + _lineSize*y + x] = (!_clear?Printer::Visuals::BLOCK:Printer::Visuals::EMPTY);
    }
}

void Game::PrepareBoard(bool _print) {

    int sizeInc = _lineSize * gBoardRules.gameHeight;

    // Alloc space.
    _gameBoard = (Printer::Visuals*)malloc(sizeInc * sizeof(Printer::Visuals));

    if (_print) wprintf(L"Board size: %i.\n", sizeInc);

    if (_print) wprintf(L"Allocated memory space.\n");

    // Top border line.
    for (int i = 0; i < _lineSize-1; i++) {
        _gameBoard[i] = Printer::Visuals::BORDERH;
    }
    _gameBoard[_lineSize] = Printer::Visuals::NEWLINE;

    if (_print) wprintf(L"Wrote top border line.\n");

    // Loop for the game board.
    for (int i = 0; i < gBoardRules.gameHeight - 2; i++) {
        // First border.
        _gameBoard[_lineSize * (i + 1) + 1] = Printer::Visuals::BORDERV;
        // Blank spaces.
        for (int j = 2; j < _lineSize - 1; j++) {
            _gameBoard[_lineSize * (i + 1) + j] = Printer::Visuals::EMPTY;
        }
        // Last border.
        _gameBoard[_lineSize * (i + 1) + _lineSize - 1] = Printer::Visuals::BORDERV;
        // Newline
        _gameBoard[_lineSize * (i + 1) + _lineSize] = Printer::Visuals::NEWLINE;
    }

    if (_print) wprintf(L"Wrote game board.\n");

    // Bottom border line.
    for (int i = 0; i < _lineSize - 1; i++) {
        _gameBoard[sizeInc - _lineSize + i + 1] = Printer::Visuals::BORDERH;
    }
    _gameBoard[sizeInc - 1] = Printer::Visuals::NEWLINE;

    if (_print) wprintf(L"Wrote bottom border line.\n");
}

void Game::PrintBoard() {
 
    // Clear screen.
    clear();
    int sizeInc = _lineSize * gBoardRules.gameHeight;
    int y = 0, x=0;

    for (int i = 0; i < sizeInc; i++) {
        if (_gameBoard[i] == Printer::Visuals::NEWLINE) {
            y++;
            x = 0;
        }
        else
        {
            mvaddch(y, x, Printer::pMap_[_gameBoard[i]]);
            x++;
        }
    }
    refresh();
}


