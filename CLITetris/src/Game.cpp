#include <Game.h>
using namespace std;

TetrominoNode *gQueueHead, *gQueueTail;
GameStatus gGameStatus;

Game::Game(bool print) {
    // The game is ready to start.
    Game::GenerateRandomTetrominoQueue(print);
    gGameStatus = START;
}



void Game::GenerateRandomTetrominoQueue(bool _print) {
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

    // Shuffling our array
    shuffle(shuffleData, shuffleData + TETRO_QUEUE_SIZE,
        default_random_engine(seed));

    // Printing array (for debug testing).
    if (_print) {
        for (int i = 0; i < TETRO_QUEUE_SIZE; i++)
            wprintf(L"%i ", shuffleData[i]);
        wprintf(L"\n");
    }

    // Creating linked list based on the randomized array.
    TetrominoNode *fill_ptr = (TetrominoNode*)malloc(sizeof(TetrominoNode));
    fill_ptr->value = shuffleData[0];
    fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
    fill_ptr = fill_ptr->next;
    gQueueHead = fill_ptr;
    for (int i = 1; i < TETRO_QUEUE_SIZE; i++)
    {
        fill_ptr->value = shuffleData[i];
        fill_ptr->next = (TetrominoNode*)malloc(sizeof(TetrominoNode));
        fill_ptr = fill_ptr->next;
        gQueueTail = fill_ptr;
        fill_ptr->next = NULL;
    }
    gQueueTail->next = gQueueHead;
}


Piece::Tetromino TakeFromTetrominoQueue() {
    Piece::Tetromino result = gQueueHead->value;
    gQueueHead = gQueueHead->next;
    return result;
}

void Game::Update() {
    
}

void Game::StartGame() {
    ManageConsoleMode(true);                    // Enabling input processing for game mode.
    while (gGameStatus != OVER) {               // The game cycle starts here.
        //KeyBind nextMove = _snake->direction;   // The default input resets to the snake default/latest direction.


        //win32_TimeStep(nextMove, _snake, hStdIn, cNumRead, irInBuf);
        //FlushConsoleInputBuffer(hStdIn);


        //endGame = _snake->Move(nextMove); // This step processes the whole snake movement and game status.
    }
}