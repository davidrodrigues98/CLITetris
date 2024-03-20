#include <Game.h>
using namespace std;

TetrominoNode *gQueueHead, *gQueueTail, *gQueueCurrent;
TetrominoRotateNode *gRotateHead, *gRotateTail, *gRotateCurrent;
GameStatus gGameStatus;

void CreateDoublyLinkedListPointer(
    Piece::Block _r0p[4],
    Piece::Block _r0n[4],
    Piece::Block _r1p[4],
    Piece::Block _r1n[4],
    Piece::Block _r2p[4],
    Piece::Block _r2n[4],
    Piece::Block _r3p[4],
    Piece::Block _r3n[4]
)
{
    //r0 Original Position
    gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
    gRotateTail->relativeCoordinatesPrev = _r0p;
    gRotateTail->relativeCoordinatesNext = _r0n;
    gRotateTail->prev = gRotateHead;

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

    //r3
    gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
    gRotateHead->relativeCoordinatesPrev = _r3p;
    gRotateHead->relativeCoordinatesNext = _r3n;
    aux->next = gRotateHead;
    gRotateHead->prev = aux;
    gRotateHead->next = gRotateTail;

    gRotateCurrent = gRotateTail;
}

void CreateRotateMaskForTetromino(Piece::Tetromino _tetromino) {

    switch (_tetromino)
    {
    case Piece::L: {
        Piece::Block lr0p[4] =
        {
            { -1, 0 }, { 0,1 }, { 1,2 }, { 2,1 }
        };
        Piece::Block lr0n[4] =
        {
            {0,-2},{-1,-1},{-2,0},{-1,1}
        };
        Piece::Block lr1p[4] =
        {
            {-2,-1},{-1,0},{0,1},{1,0}
        };
        Piece::Block lr1n[4] =
        {
            {0,-2},{-1,-1},{-2,0},{-1,1}
        };
        Piece::Block lr2p[4] =
        {
            {1,-1},{0,0},{-1,1},{0,2}
        };
        Piece::Block lr2n[4] =
        {
            {2,1},{1,0},{0,-1},{-1,0}
        };
        Piece::Block lr3p[4] =
        {
            {1,0},{0,-1},{-1,-2},{-2,-1}
        };
        Piece::Block lr3n[4] =
        {
            {1,1},{0,0},{1,-1},{0,-2}
        };
        CreateDoublyLinkedListPointer(lr0p, lr0n, lr1p, lr1n, lr2p, lr2n, lr3p, lr3n);
        break;
    }
    case Piece::J: {
        Piece::Block jr0p[4] =
        {
            { 1, 2 }, { 0,1 }, { -1,0 }, { 0,-1 }
        };
        Piece::Block jr0n[4] =
        {
            {0,0},{1,1},{0,2},{-1,1}
        };
        Piece::Block jr1p[4] =
        {
            {-2,0},{-1,-1},{0,-2},{1,-1}
        };
        Piece::Block jr1n[4] =
        {
            {0,1},{-1,0},{1,0},{2,1}
        };
        Piece::Block jr2p[4] =
        {
            {0,-1},{1,0},{2,1},{1,2}
        };
        Piece::Block jr2n[4] =
        {
            {-1,1},{0,0},{1,-1},{2,0}
        };
        Piece::Block jr3p[4] =
        {
            {1,-1},{0,0},{-1,1},{-2,0}
        };
        Piece::Block jr3n[4] =
        {
            {-1,-2},{0,-1},{0,-1},{1,-2}
        };
        CreateDoublyLinkedListPointer(jr0p, jr0n, jr1p, jr1n, jr2p, jr2n, jr3p, jr3n);
        break;
    }
    case Piece::I: {

        // r1
        gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block ir1[4] = {
            {0,0},{-1,1},{-2,2},{-3,3}
        };
        gRotateTail->relativeCoordinatesPrev = ir1;
        gRotateTail->relativeCoordinatesNext = ir1;
        gRotateTail->next = gRotateHead;
        gRotateTail->prev = gRotateHead;

        // r0 Original position.
        gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block ir0[4] = {
            {0,0},{1,-1},{2,-2},{3,-3}
        };
        gRotateHead->relativeCoordinatesPrev = ir0;
        gRotateHead->relativeCoordinatesNext = ir0;
        gRotateHead->next = gRotateTail;
        gRotateHead->prev = gRotateTail;
        gRotateCurrent = gRotateHead;

        break;
    }
    case Piece::T: {
        Piece::Block tr0p[4] =
        {
            {-1, 1}, {0,0}, {1,-1}, {1,-1}
        };
        Piece::Block tr0n[4] =
        {
            {0, 1}, {1, 0}, {0, -1}, {2, -1}
        };
        Piece::Block tr1p[4] =
        {
            {0, -1}, {1, 0}, {0, 1}, {2, 1}
        };
        Piece::Block tr1n[4] =
        {
            {0, 0}, {-1, 1}, {0, 0}, {-2, 2}
        };
        Piece::Block tr2p[4] =
        {
            {0, -1}, {1, -1}, {0, 0}, {2, -2}
        };
        Piece::Block tr2n[4] =
        {
            {-1, 0}, {0, -1}, {1, 0}, {1, -2}
        };
        Piece::Block tr3p[4] =
        {
            {1, 0}, {0, 1}, {-1, 0}, {-1, 2}
        };
        Piece::Block tr3n[4] =
        {
            {1, -1}, {0, 0}, {-1, 1}, {-1, 1}
        };
        CreateDoublyLinkedListPointer(tr0p, tr0n, tr1p, tr1n, tr2p, tr2n, tr3p, tr3n);
        break;
    }
    case Piece::S: {
        // r1
        gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block sr1[4] = {
            {0,-1},{-1,0},{0,1},{-1,2}
        };
        gRotateTail->relativeCoordinatesPrev = sr1;
        gRotateTail->relativeCoordinatesNext = sr1;
        gRotateTail->next = gRotateHead;
        gRotateTail->prev = gRotateHead;

        // r0 Original position.
        gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block sr0[4] = {
            {0,1},{1,0},{0,-1},{1,-2}
        };
        gRotateHead->relativeCoordinatesPrev = sr0;
        gRotateHead->relativeCoordinatesNext = sr0;
        gRotateHead->next = gRotateTail;
        gRotateHead->prev = gRotateTail;
        gRotateCurrent = gRotateHead;
        break;
    }
    case Piece::Z: {
        // r1
        gRotateTail = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block zr1[4] = {
            {1,0},{0,1},{-1,0},{-2,1}
        };
        gRotateTail->relativeCoordinatesPrev = zr1;
        gRotateTail->relativeCoordinatesNext = zr1;
        gRotateTail->next = gRotateHead;
        gRotateTail->prev = gRotateHead;

        // r0 Original position.
        gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
        Piece::Block zr0[4] = {
            {-1,0},{0,-1},{1,0},{2,-1}
        };
        gRotateHead->relativeCoordinatesPrev = zr0;
        gRotateHead->relativeCoordinatesNext = zr0;
        gRotateHead->next = gRotateTail;
        gRotateHead->prev = gRotateTail;
        gRotateCurrent = gRotateHead;
        break;
    }
    case Piece::O: { // Special case, loop into same node with empty value to still validate the rotation for a square.
        gRotateHead = (TetrominoRotateNode*)malloc(sizeof(TetrominoRotateNode));
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
            wprintf(L"[%i %i] ", (blocks + i)->x, (blocks + i)->y);
        }
        wprintf(L"\n");
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

Piece::Tetromino TakeFromTetrominoQueue() {
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


