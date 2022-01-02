#include <string>

namespace Firefly {
struct Project {
    std::string rootPath = "";
};

class EditorState {
public:
    static EditorState& Get() {
        static EditorState state;
        return state;
    }

    static Project& CurrentProject() {
        return Get().currentProject;
    }
    
private:
    Project currentProject;
};
}
