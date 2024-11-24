#include "include/Utils.hpp"
#include <iostream>
#include <map>

int main() {
    std::map<std::string, void (*)()> commands = {
        {"add_flashcard", add_flashcard},
        {"review_today", review_today},
        {"get_report", get_report},
        {"get_progress_report", get_progress_report},
        {"streak", streak},
        {"next_day", next_day}};

    std::string command;
    while (std::cin >> command)
        if (commands.find(command) != commands.end())
            commands[command]();

    return 0;
}
