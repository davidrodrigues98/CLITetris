// CLITetris.cpp : Defines the entry point for the application.
//

#include "CLITetris.h"
#include "Main.h"

using namespace std;


int BeforeInitialize() {
	int res = 0;
	_setmode(_fileno(stdout), _O_U8TEXT);
	res++;
	return res;
}

int main()
{
	BeforeInitialize();
	Initialize();
}
