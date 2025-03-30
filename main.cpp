#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class PromptSystem 
{
private:
    std::vector<std::string> prompts;
    int delay_ms = 2000;


public:
        
        void add_prompt(const std::string& text) {
            prompts.push_back(text);
        }

        void set_delay(int ms) {
            delay_ms = ms;
        }

        void run() const {
            for (const std::string& line : prompts) {
                std::cout << line << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

            }
        }

        void clear() {
            prompts.clear();
        }
};

int main() 
{
    std::string first_name, last_name;

    //prompt first name
    std::cout << "what do they call you Gender? ";
    std::cin >> first_name; //only captures the first word
    
    // Dialogue
    std::cout << "I don' reckin the name\n";
    std::cout << "...\n";
    std::cout << "Ya knowww...\n";

    //Prompt last name
    std::cout << "what's yee last name, mate? ";
    std::cin >> last_name; // also captures only first word

    // output full name
    std::cout << "Well, Howdy " << first_name << " " << last_name << "!" << std::endl;

    return 0;
}
