#pragma once

#include <CLITetris.h>

typedef enum Visuals {
	BLOCK,
	EMPTY,
	BORDERV,
	BORDERH
};

int ConsolePrint(Visuals _visual);