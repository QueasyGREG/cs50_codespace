#include "Dialogue.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <termios.h>

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

Text& Text::set_delay(int ms) {
    delay_ms = ms;
    return *this;
}

Text& Text::add_text(const std::string& label, bool wait) {
    texts.push_back({label, wait});
    return *this;
}

Text& Text::add_texts(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        add_text(line);
    }
    return *this;
}

void Text::run(bool keep_texts) {
    for (const auto& t : texts) {
        std::cout << t.label << std::endl;

        if (t.wait) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            std::cout << "[Press SPACE to continue...]" << std::flush;
            while (getch() != ' ') {}
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }

        std::cout << std::endl;
    }

    if (!keep_texts) {
        texts.clear();
    }
}
