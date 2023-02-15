#include <Printer.h>

std::map<Visuals, const wchar_t> PrintMap = {
	{BLOCK, L'\u2588'},
	{EMPTY, L'\u00A0'},
	{BORDERV, L'\u2551'},
	{BORDERH, L'\u2550'}
};

int ConsolePrint(Visuals _visual) {
	wprintf(L"%c", PrintMap[_visual]);
	return 0;
}