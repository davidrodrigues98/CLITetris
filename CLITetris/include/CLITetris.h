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
#include <thread>
#include <curses.h>

#include <Global.h>

// Reference additional headers your program requires here.

#pragma region Global macro definitions.
// Tetromino queue size of array.
#define TETRO_QUEUE_SIZE 7
#define INPUT_RECORD_BUFFER_SIZE 20
#define stringify( name ) # name
#pragma endregion

/// <summary>
/// Prepares the opened command line interface to handle the user game events.
/// </summary>
/// <param name="_gameMode">(Optional) What is the gamemode being prepared?</param>
void ManageConsoleMode(bool _gameMode = true);

/// <summary>
/// Applies system configurations before starting the application logic.
/// </summary>
///  <returns>The amount of functions ran.</returns>
int BeforeInitialize();

/// <summary>
/// Standard program initialization.
/// </summary>
/// <param name="_dev">= true if the application must start in developer mode.</param>
/// <returns>0</returns>
int Initialize(bool _dev = false);

///<summary>
/// Function for testing purposes while developing or updating.
///</summary>
///<returns>0</returns>
int devInitialize();