#include "window/window.h"
#include "editorWindow.h"

int main() {
    Firefly::EditorWindow window;
    window.Create("Editor (WIP)", 1920, 1080);
    window.Update();
    window.Cleanup();
}