#pragma once

/// <summary>
/// General variables to print and control game board.
/// </summary>
typedef struct BoardRules {
	int gameWidth = 10;
	int gameHeight = 20;
} BoardRules;

static BoardRules gBoardRules = BoardRules();