#pragma once

/// <summary>
/// General variables to print and control game board.
/// </summary>
typedef struct BoardRules {
	int gameWidth = 13;
	int gameHeight = 22;
} BoardRules;

static BoardRules gBoardRules = BoardRules();