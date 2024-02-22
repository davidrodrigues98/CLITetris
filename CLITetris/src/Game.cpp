#include <Game.h>
using namespace std;

TetrominoNode *gQueueHead, *gQueueTail, *gQueueCurrent;
GameStatus gGameStatus;

KeyBind KeyEventProc(KEY_EVENT_RECORD ker)
{
    WORD recordedKeyCode = ker.wVirtualKeyCode;
    KeyBind result = IDLE;

    // Virtual key mapping.
    switch (recordedKeyCode)
    {
    case 37: result = LEFT; /*wprintf(L"LEFT\n")*/; break;
        //? case 38: result = UP;  break;
    case 39: result = RIGHT; /*wprintf(L"RIGHT\n")*/; break;
        //? case 40: result = DOWN; break;
    }

    return result;
}

Game::Game(bool _doubleBag, bool _print) {
    Game::GenerateRandomTetrominoQueue(_doubleBag, _print);
    // Setting new game status.
    gGameStatus = START;
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
            if(_print) wprintf(L"DOWN\n");
            MoveDown();
            break;
        case KeyBind::LEFT:
            if(_print) wprintf(L"LEFT\n");
            MoveLeft();
            break;
        case KeyBind::RIGHT:
            if(_print) wprintf(L"RIGHT\n");
            MoveRight();
            break;
        case KeyBind::ROTATE_LEFT: break;
        case KeyBind::ROTATE_RIGHT: break;
    }
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
    PrepareBoard(true);
    gGameStatus = GameStatus::START;
}

void Game::UpdateBoard(bool _clear) {
    Piece::Block* blocks = _activePiece->_blocks;
    int lineSize = (2 + gBoardRules.gameWidth + 1);
    for (int i = 0; i < 4; i++) {
        int x = (blocks+i)->x;
        int y = (blocks+i)->y;
        _gameBoard[lineSize + lineSize*y + x + 1] = (!_clear?Printer::Visuals::BLOCK:Printer::Visuals::EMPTY);
    }
}

void Game::PrepareBoard(bool _print) {
    /* Board size:
        (2 (Borders) + Width + 1 (Breakline)) -> First line. 
      + (2 (Borders) + Width + 1 (Breakline) * Height) -> Game Lines.
      + (2 (Borders) + Width + 1 (Breakline)) -> Last line.
    */
    int lineSize = (2 + gBoardRules.gameWidth + 1);
    int sizeInc = (lineSize * 2)
                + (lineSize * gBoardRules.gameHeight);

    // Alloc space.
    _gameBoard = (Printer::Visuals*)malloc(sizeInc * sizeof(Printer::Visuals));

    if (_print) wprintf(L"Allocated memory space.\n");

    // Top border line.
    for (int i = 0; i < lineSize-1; i++) {
        _gameBoard[i] = Printer::Visuals::BORDERH;
    }
    _gameBoard[lineSize] = Printer::Visuals::NEWLINE;

    if (_print) wprintf(L"Wrote top border line.\n");

    // Loop for the game board.
    for (int i = 0; i < gBoardRules.gameHeight; i++) {
        // First border.
        _gameBoard[lineSize * (i + 1) + 1] = Printer::Visuals::BORDERV;
        // Blank spaces.
        for (int j = 2; j < lineSize - 1; j++) {
            _gameBoard[lineSize * (i + 1) + j] = Printer::Visuals::EMPTY;
        }
        // Last border.
        _gameBoard[lineSize * (i + 1) + lineSize - 1] = Printer::Visuals::BORDERV;
        // Newline
        _gameBoard[lineSize * (i + 1) + lineSize] = Printer::Visuals::NEWLINE;
    }

    if (_print) wprintf(L"Wrote game board.\n");

    // Bottom border line.
    for (int i = 0; i < lineSize; i++) {
        _gameBoard[sizeInc - lineSize + i + 1] = Printer::Visuals::BORDERH;
    }
    _gameBoard[sizeInc - 1] = Printer::Visuals::NEWLINE;

    if (_print) wprintf(L"Wrote bottom border line.\n");
}

void Game::PrintBoard() {
    system("cls");
    int lineSize = (2 + gBoardRules.gameWidth + 1);
    int sizeInc = (lineSize * 2)
        + (lineSize * gBoardRules.gameHeight);
    for (int i = 0; i < sizeInc; i++) {
        Printer::ConsolePrint(_gameBoard[i]);
    }
}