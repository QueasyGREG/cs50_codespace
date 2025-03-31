#include "input_util.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

std::string to_lower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string timed_input_with_idle_hint(const std::string& hint, int idle_ms) {
    std::string input;
    auto start = std::chrono::steady_clock::now();

    std::thread hint_thread([&]() {
        while (input.empty()) {
            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

            if (duration.count() >= idle_ms) {
                std::cout << hint << std::endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::getline(std::cin, input);
    hint_thread.join();

    return input;
}
