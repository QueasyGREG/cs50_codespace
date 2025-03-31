#pragma once
#include <string>
#include <vector>

struct TextLine {
    std::string label;
    bool wait = false;
};

class Text {
private:
    std::vector<TextLine> texts;
    int delay_ms = 2000;

public:
    Text& set_delay(int ms);
    Text& add_text(const std::string& label, bool wait = false);
    Text& add_texts(const std::vector<std::string>& lines);
    void run(bool keep_texts = false);
};
