#include <Game.h>

using namespace std;

KeyBind KeyEventProc(KEY_EVENT_RECORD ker)
{
    WORD recordedKeyCode = ker.wVirtualKeyCode;
    KeyBind result = IDLE;

    // Virtual key mapping.
    switch (recordedKeyCode)
    {
    case 37: result = KeyBind::kbLEFT;         break;
    case 38: result = KeyBind::ROTATE_RIGHT; break;
    case 39: result = KeyBind::kbRIGHT;        break;
    case 40: result = KeyBind::ROTATE_LEFT;  break;
    default: result = KeyBind::IDLE;         break;
    }

    return result;
}

void Game::GenerateRandomTetrominoQueue(bool _double_bag, bool _print) {
    // Fixed array to support the starting randomization.
    Tetromino shuffleData[TETRO_QUEUE_SIZE] = {
        Tetromino::O,
        Tetromino::L,
        Tetromino::J,
        Tetromino::I,
        Tetromino::T,
        Tetromino::S,
        Tetromino::Z
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
        Tetromino shuffleData2[TETRO_QUEUE_SIZE] = {
            Tetromino::O,
            Tetromino::L,
            Tetromino::J,
            Tetromino::I,
            Tetromino::T,
            Tetromino::S,
            Tetromino::Z
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

Tetromino Game::TakeFromTetrominoQueue() {
    Tetromino result = gQueueCurrent->value;
    gQueueCurrent = gQueueCurrent->next;
    return result;
}

Tetromino Game::TakeFromTetrominoQueue(Tetromino _debugTetType) {
    return _debugTetType;
}

bool Game::Update(KeyBind _nextAction, bool _print) {
    bool returning = false;
    switch (gGameStatus) {
    case GameStatus::PLACE: {
        _activePiece = new Piece(TakeFromTetrominoQueue());
        if (_print)
            wprintf(L"Debug: Game::Update - Active piece is tetromino: %i\n", _activePiece->tetromino);
        gGameStatus = GameStatus::MOVE;
        _stepdownCount = 0;
        break;
    }
    case GameStatus::MOVE:
        UpdateBoard(true);
        returning = ProcessMovement(_nextAction, _print);
        UpdateBoard();
        break;
    }
    return returning;
}

bool Game::ProcessMovement(KeyBind _nextAction, bool _print) {
    bool returning = false;
    switch (_nextAction) {
        case DOWN: 
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"Debug: Game::ProcessMovement -> DOWN\n");
                MoveDown();
            }
            else {
                if (_stepdownCount <= 1)
                    returning = true;
                else
                Land();
            }
            break;
        case kbLEFT:
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"Debug: Game::ProcessMovement -> LEFT\n");
                MoveLeft();
            }
            break;
        case kbRIGHT:
            if (ValidateMove(_nextAction)) {
                if (_print) wprintf(L"Debug: Game::ProcessMovement -> RIGHT\n");
                MoveRight();
            }
            break;
        // TBD rotate validation
        case ROTATE_LEFT:
            if (_print) wprintf(L"Debug: Game::ProcessMovement -> ROTATE_LEFT");
            RotateLeft();
            break;
        case ROTATE_RIGHT: 
            if (_print) wprintf(L"Debug: Game::ProcessMovement -> ROTATE_RIGHT");
            RotateRight();
            break;
    }
    return returning;
}

void Game::RotateLeft() {
    _activePiece->RotatePiece(PieceBlockRotation::LEFT);
    ValidateRotation(PieceBlockRotation::LEFT);
}

void Game::RotateRight() {
    _activePiece->RotatePiece(PieceBlockRotation::RIGHT);
    ValidateRotation(PieceBlockRotation::RIGHT);
}

void Game::ValidateRotation(PieceBlockRotation _direction) {
    Block* blocks = _activePiece->_blocks;
    bool revert = false;
    for (int i = 0; i < 4; i++) {
        int x = (blocks + i)->x;
        int y = (blocks + i)->y;
        if (_gameBoard[_lineSize + _lineSize * y + x] >= 10)
            revert = true;
    }
    if (revert == true)
        _activePiece->RotatePiece((_direction == PieceBlockRotation::RIGHT ? PieceBlockRotation::LEFT : PieceBlockRotation::RIGHT));
}

bool Game::ValidateMove(KeyBind _action) {
    Block* blocks = _activePiece->_blocks;
    int nX = 0, nY = 0;
    switch (_action) {
        case kbLEFT:
            nX = -1;
        break;
        case kbRIGHT:
            nX = 1;
        break;
        case DOWN:
            nY = 1;
        default:break;
    }
    for (int i = 0; i < 4; i++) {
        int x = (blocks + i)->x;
        int y = (blocks + i)->y;

        // Condition logic: Visual enumerator >10 means that it is a border or a placed block.
        Printer::Visuals cell = _gameBoard[_lineSize + _lineSize * (y + nY) + x + nX];
        if (cell >= 10)
            return false;
    }
    return true;
}

void Game::PlaceBlocks() {
    for (int i = 0; i < 4; i++)
    {
        Block* blocks = _activePiece->_blocks;
        int x = (blocks + i)->x;
        int y = (blocks + i)->y;
        _gameBoard[_lineSize + _lineSize * y + x] = Printer::Visuals::PLACED_BLOCK;
    }
}

void Game::Land() {
    gGameStatus = WAIT;
    PlaceBlocks();
    delete(_activePiece);
    _activePiece = nullptr;
    Demolish();
    gGameStatus = PLACE;
}

void Game::Demolish() {
    // For each line...
    for (int i = 0; i < gBoardRules.gameHeight - 2; i++) {
        bool score = true;
        // ... verify if all blocks are filled.
        for (int j = 2; j < _lineSize - 1; j++) {
            if (_gameBoard[_lineSize * (i + 1) + j] == Printer::Visuals::EMPTY)
                score = false;
        }
        // If they are all filled, we demolish the line.
        if (score == true) {
            // Update score.
            Scored();
            for (int j = i; j != 0; j--) {
                for (int k = 2; k < _lineSize - 1; k++) {
                    // Clean the line.
                    Printer::Visuals *ptr = &_gameBoard[_lineSize * (j + 1) + k];
                    *ptr = _gameBoard[_lineSize * j + k];
                }
            }
        }
    }
}

void Game::Scored() {
    // TBD
}

void Game::MoveDown() {
    Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->y++;
    }
    _stepdownCount++;;
}

void Game::MoveLeft() {
    Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->x--;
    }
}

void Game::MoveRight() {
    Block* blocks = _activePiece->_blocks;
    for (int i = 0; i < 4; i++) {
        (blocks + i)->x++;
    }
}

void Game::StartGame() {
    PrepareBoard();
    gGameStatus = GameStatus::PLACE;
}

void Game::UpdateBoard(bool _clear) {
    if (_activePiece != nullptr) {
        Block* blocks = _activePiece->_blocks;
        for (int i = 0; i < 4; i++) {
            int x = (blocks + i)->x;
            int y = (blocks + i)->y;
            _gameBoard[_lineSize + _lineSize * y + x] = (!_clear ? Printer::Visuals::BLOCK : Printer::Visuals::EMPTY);
        }
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

void Game::DestroyLL(TetrominoNode** head) {
    TetrominoNode* current = *head;
    TetrominoNode* next = NULL;
    if (current != nullptr)
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != *head);
    *head = NULL;
}

Game::Game(bool _doubleBag, bool _print) {
    Game::GenerateRandomTetrominoQueue(_doubleBag, _print);
    // Setting new game status.
    gGameStatus = PLACE;
    // Calc size of each line.
    _lineSize = gBoardRules.gameWidth;
}

Game::~Game() {
    free(_gameBoard);               // Clear memory for game board.
    
    gQueueCurrent = nullptr;        // Reset other linked list variables.
    gQueueTail = nullptr;
    
    DestroyLL(&gQueueHead);         // Clear memory for tetromino queue.
    
    if(_activePiece != nullptr)     // Calls destructor for active piece if that was not done yet.
        delete(_activePiece);
}
