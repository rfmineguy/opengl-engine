#include <iostream>
#include "window/window.h"

#define VERSION_MINOR 3
#define VERSION_MAJOR 3


//cool debugger added to neovim
// f9 -> breakpoint

int main() {
    Window window;
    window.Create("OpenGL Window", 600, 600);
    window.Update();
    window.Cleanup();

    return 0;
}
