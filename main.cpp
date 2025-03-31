// Aurthor: Adam Britt
// Date created: 3/30/25
// File name: main.cpp
// File description:

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <unordered_map>

// Minimal keypress function for Linux (used only when needed)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);          // get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new settings
    ch = getchar();                          // get a single character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore settings
    return ch;
}

// Encapsulated prompt with text and optional wait flag
struct TextLine {
    std::string label;
    bool wait = false;
};

class Text 
{
private:
    std::vector<TextLine> texts;
    int delay_ms = 2000;


public:
        // Set the delay between texts
        void set_delay(int ms) {
            delay_ms = ms;
        }        

        // Add a single text
        Text& add_text(const std::string& label,bool wait = false) {
            texts.push_back({label,wait});
            return *this;
        }

        // Add multiple texts at once
        Text& add_texts(const std::vector<std::string>& lines) {
            for (const auto& line : lines) {
                add_text(line); // uses default wait = false
            }
            return *this;
        }
        
        // Show texts one by one with delay
        void run(bool keep_texts = false) {
            for (const auto& t : texts) {
                std::cout << t.label << std::endl;
                if (t.wait) {
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

        // Clear the list of texts
        void clear() {
            texts.clear();
        }
};

// Optional: lowercase conversion helper
std::string to_lower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main()
{
    std::string gender_input, gender_term;
    std::string first_name, last_name;
    
     // Map gender inputs to internal term
     std::unordered_map<std::string, std::string> gender_map = {
        {"female", "girl"},
        {"girl", "girl"},
        {"woman", "girl"},
        {"male", "boy"},
        {"boy", "boy"},
        {"man", "boy"}
    };

    Text text;
    text.set_delay(1500); // Customize timing between lines
    // Ask for gender
    text.add_text("What gender are you? (female/girl/woman or male/boy/man):", true).run();
    std::cin >> gender_input;

    gender_input = to_lower(gender_input);
    if (gender_map.count(gender_input)) {
        gender_term = gender_map[gender_input];
    } else {
        gender_term = "stranger";
    }

    // Ask for first name
    text.add_text("What do they call you " + gender_term + "?", true).run();
    std::cin >> first_name;

    // Build up flavor text
    text.add_texts({
        "I don' reckin the name...",
        "...",
        "Ya knowww..."
    });

    text.add_text("What's yee last name, mate?", true).run();
    std::cin >> last_name;

    // Final greeting
    text.add_text("Well, Howdy " + first_name + " " + last_name + "!").run();

    return 0;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
    /*// Start dialouge ask for first name with pause
    text.add_text("what do they call you Gender? ", true); // waits for input
    text.run();

    text.clear();
    std::cin >> first_name;

    text.clear(); // Prepare for the next text sequence
   
  


}

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
*/