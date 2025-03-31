# cs50_codespace
                ┌──────────────────────────┐
                │  VS Code Desktop (local) │◄────────────┐
                │  "Fast UI, editing tools"│             │
                └──────────┬───────────────┘             │
                           │                             │
               Edit Code Locally                         │
                           │                             │
                    git add .                            │
                           │                             │
                    git commit -m "..."                  │
                           │                             │
                    git push origin main  ───────────────┘
                           │
                           ▼
                ┌────────────────────────┐
                │      GitHub Repo       │
                │  "Cloud source of truth"│
                └──────────┬─────────────┘
                           │
                           ▼
         ┌────────────────────────────────────┐
         │  GitHub Codespace (Cloud)          │
         │  "Linux tools, g++, make, gdb..."  │
         └────────────────────────────────────┘
                           ▲
                   git pull origin main
                           ▲
             Sync down changes to Codespace


// Code Structure


// Includes (external libraries)
#include <...>

// Class definition
class PromptSystem {
private:
    // Data members (prompts, delay)
public:
    // Methods like add_prompt(), run(), set_delay()
};

// main() function
int main() {
    // Your gameplay/dialogue logic
}
