#include <Piece.h>

void ManageConsoleMode(bool _gameMode = true);

/// <summary>
/// Class for game logic.
/// In game memory and steps validation.
/// Each instance is a round of a game.
/// </summary>
class Game {
protected:
	vector<Piece> _piece;
	Piece::Tetromino * _tetrominoQueueLL;

	/// <summary>
	/// Function that generates the starting pieces.
	/// </summary>
	/// <param name="_officialRules"> Should the algorithm use the official sequence rule, or total randomization?</param>
	void GenerateRandomTetrominoQueue(bool _officialRules = true);

	/// <summary>
	/// Takes the first piece from the queue and inserts one more at the last.
	/// </summary>
	/// <returns></returns>
	Piece::Tetromino TakeFromTetrominoQueue();
public:
	/// <summary>
	/// Constructor for menu-based parameters.
	/// </summary>
	/// <param name="_gameSpeed">stands for game speed in milisseconds (ms).</param>
	Game(int _gameSpeed);

	/// <summary>
	/// Constructor for the defaut parameters taken from the configuration files (.cfg).
	/// </summary>
	Game();
};