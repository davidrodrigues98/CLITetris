#include <Game.h>
using namespace std;


Game::Game(bool print) {
    //? this->_tetrominoQueueLL = (Piece::Tetromino*)malloc(7 * sizeof(Piece::Tetromino));
    Game::GenerateRandomTetrominoQueue(print);
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
}