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
            ProcessMovement(_nextAction, _print);
            break;
    }
}

void Game::ProcessMovement(KeyBind _nextAction, bool _print) {
    switch (_nextAction) {
        case KeyBind::DOWN: 
            wprintf(L"DOWN\n");
            break;
        case KeyBind::LEFT:
            wprintf(L"LEFT\n");
            break;
        case KeyBind::RIGHT:
            wprintf(L"RIGHT\n");
            break;
        case KeyBind::ROTATE_LEFT: break;
        case KeyBind::ROTATE_RIGHT: break;
    }
}

void Game::StartGame() {
    //? while (gGameStatus != OVER) {               // The game cycle starts here.
    gGameStatus = GameStatus::START;
    //? }
}