// CLITetris.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>

// Reference additional headers your program requires here.

//? #include <Main.h>
//? #include <Config.h>

#pragma region Global program definitions.
// Tetromino queue size of array.
#define TETRO_QUEUE_SIZE 7
#define INPUT_RECORD_BUFFER_SIZE 2
#pragma endregion

/// <summary>
/// Applies system configurations before starting the application logic.
/// </summary>
///  <returns>The ammount of functions ran.</returns>
int BeforeInitialize();

/// <summary>
/// Prepares the opened command line interface to handle the user game events.
/// </summary>
/// <param name="_gameMode">(Optional) What is the gamemode being prepared?</param>
void ManageConsoleMode(bool _gameMode = true);

int Initialize(bool _dev = false);

///<summary>
/// Function for testing purposes while developing or updating.
///</summary>
///<returns>0</returns>
int devInitialize();