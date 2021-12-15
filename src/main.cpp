#include <iostream>
#include "window/window.h"

#define VERSION_MINOR 3
#define VERSION_MAJOR 3


//cool debugger added to neovim
// f9 -> breakpoint
using namespace Firefly;
int main() {
    Window window;
    window.Create("Firefly Engine", 1920, 1080);
    window.Update();
    LOG_INFO("Left update");
    window.Cleanup();
    
    return 0;
}
