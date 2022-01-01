#include "window/window.h"
#include "editorWindow.h"

int main() {
    Firefly::EditorWindow window;
    window.Create("Editor", 600, 600);
    window.Update();
    window.Cleanup();
}
