#include <Printer.h>

	Printer::PrintMap Printer::pMap_ = {
		{ BLOCK, L'\u2588' },
		{ EMPTY, L'\u00A0' },
		{ BORDERV, L'\u2551' },
		{ BORDERH, L'\u2550' },
		{ NEWLINE, L'\n' }
	};

int Printer::ConsolePrint(Printer::Visuals _visual) {
	wprintf(L"%c", Printer::pMap_[_visual]);
	return 0;
}