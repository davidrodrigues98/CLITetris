﻿#pragma once
#include <CLITetris.h>

/// <summary>
/// Class to define an interface to print the game visuals into the CLI.
/// </summary>
static class Printer {
public:
	/// <summary>
	/// Interface structure with all the possible printing options.
	/// </summary>
	typedef enum Visuals {
		BLOCK	= 1,
		EMPTY	= 0,
		BORDERV	= 10,
		BORDERH	= 11,
		PLACED_BLOCK = 12,
		NEWLINE = 2
	} Visuals;

	/// <summary>
	/// Map type to translate data elements into special characters on CLI.
	/// </summary>
	typedef std::map<Visuals, const wchar_t> PrintMap;

	/// <summary>
	/// Static print translator.
	/// </summary>
	static PrintMap pMap_;

};