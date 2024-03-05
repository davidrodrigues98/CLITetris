#include <Printer.h>

Printer::PrintMap Printer::pMap_ = {
	{ BLOCK, L'\u2588' },
	{ EMPTY, L' ' },
	{ BORDERV, L'\u2551' },
	{ BORDERH, L'\u2550' },
	{ NEWLINE, L'\n' }
};