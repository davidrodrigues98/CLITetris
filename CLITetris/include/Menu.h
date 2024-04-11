#pragma once

#include <iostream>
#include <vector>
#include <string>

class Menu {

private:
    /// <summary>
    /// Options vector.
    /// </summary>
    std::vector<std::string> options;

public:
    /// <summary>
    /// Base constructor.
    /// </summary>
    /// <param name="options">Vector with options.</param>
    Menu(const std::vector<std::string>& options) : options(options) {}

    /// <summary>
    /// Prints the menu list.
    /// </summary>
    void Display();

    /// <summary>
    /// Only allows the return of a valid integer from the option list.
    /// </summary>
    /// <returns>Selected option.</returns>
    int GetUserChoice();

    /// <summary>
    /// Starts the menu.
    /// </summary>
    /// <returns></returns>
    int Run();

};
