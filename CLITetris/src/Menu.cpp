#include <Menu.h>

void Menu::Display() {
    std::cout << "MENU:\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
}

int Menu::GetUserChoice() {
    int choice;
    std::string input;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);

        // Check if the input is a valid integer
        try {
            choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(options.size())) {
                validInput = true;
            }
            else {
                std::cout << "Invalid choice. Please enter a number between 1 and " << options.size() << ". Press ENTER key to continue.\n";
            }
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid integer. Press ENTER key to continue.\n";
        }
        catch (std::out_of_range&) {
            std::cout << "Input out of range. Please enter a valid integer. Press ENTER key to continue.\n";
        }

        // Clear the input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return choice;
}

int Menu::Run() {
    Display();
    int choice = GetUserChoice();
    return choice;
}