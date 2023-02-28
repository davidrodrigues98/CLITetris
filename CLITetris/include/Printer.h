#pragma once

#include <CLITetris.h>

typedef enum Visuals {
	BLOCK,
	EMPTY,
	BORDERV,
	BORDERH
} Visuals;

int ConsolePrint(Visuals _visual);