//#include "../registry.h"
#include "../renderer/renderer2D.h"
#include "../util/resourceManager.h"
#include "../window/inputData.h"
#include "../window/windowData.h"
#include "engineData.h"
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "imgui_file_dialog/ImGuiFileDialog.h"

#include "../util/fileUtil.h"
#include "../gameobject/entity.h"

#include "ImGuizmo/ImGuizmo.h"
#include "glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class ImGuiLayer;

namespace Firefly {
//define the editor panels
struct ImGuiMenuPanel {
    std::string selectedDirectory;

    void Draw() {
        MenuBar();
        OpenProjectModal();
    }

    void TestFileDialog() {
        // open Dialog Simple
        if (ImGui::Button("Open File Dialog"))
            //ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File", ".*,.atlas,.png,.lua,.yaml", ".");
            ImGuiFileDialog::Instance()->OpenModal("ChooseDirDlgKey", "Choose a Directory", nullptr, ".");

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) 
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                selectedDirectory = ImGuiFileDialog::Instance()->GetFilePathName();
                LOG_DEBUG("{}", selectedDirectory.c_str());
                EngineData::Get().state.openProjectRoot = selectedDirectory;
                EngineData::Get().state.currentDir = selectedDirectory;
            }
    
            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }

    void MenuBar() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::Button("New Project")) {
                    ImGui::OpenPopup("Project Creator");
                }
                NewProjectModal();
                if (ImGui::Button("Open Project")) {
                    ImGui::OpenPopup("Project Open");
                }
                OpenProjectModal();
                if (ImGui::MenuItem("New Scene")) {}
                if (ImGui::MenuItem("Save Scene")) {}
                if (ImGui::MenuItem("Open Scene")) {}
                if (ImGui::MenuItem("Close Scene")) {}
                if (ImGui::MenuItem("Open Recent")) {}
                if (ImGui::MenuItem("Quit")) {
                    WinData.shouldClose = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Copy")) {}
                if (ImGui::MenuItem("Cut")) {}
                if (ImGui::MenuItem("Paste")) {}
                if (ImGui::MenuItem("Undo")) {}
                if (ImGui::MenuItem("Redo")) {}

                ImGui::EndMenu();
            }
            //draw file dialog
            if (ImGui::BeginMenu("Window")) {
                ImGui::Checkbox("ImGuiDemoWindow", &EngineData::Preferences().isDemoWindowEnabled);
                ImGui::Checkbox("Preferences", &EngineData::Preferences().isPreferencesWindowEnabled);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }

    void NewProjectModal() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMenuButtonPosition = 1;
        if (ImGui::BeginPopupModal("Project Creator", NULL, ImGuiWindowFlags_MenuBar)) {
            ImGui::Text("Location : %s", EngineData::Get().state.openProjectRoot.c_str());// ImGui::SameLine();

            TestFileDialog();
            if (ImGui::Button("Create Project", {64, 64})) {
                if (FileUtil::CreateProjectDirectory(EngineData::Get().state.openProjectRoot)) {
                    //project already exists
                }
            }

            if (ImGui::Button("Cancel", {64, 64}))
                ImGui::CloseCurrentPopup();
                    
            ImGui::EndPopup();
        }
    }

    void OpenProjectModal() {

    }
};
struct ImGuiSignalsPanel {
    void Draw() {
        ImGui::Begin("Signals");
        if (ImGui::CollapsingHeader("Signals")) {
            ImGui::Text("Signals WIP");
        }
        ImGui::End();
    }
};
struct ImGuiResourcesPanel {
    void Draw() {
        ImGui::Begin("Resources");
        if(ImGui::CollapsingHeader("Textures")) {
            for (const auto& t : ResourceManager::Get().uTextures) {
                if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::TEXTURE, t.second.get()->tag);
            }
        }
        if (ImGui::CollapsingHeader("TextureAtlases")) {
            for (const auto& t : ResourceManager::Get().uTextureAtlases) {
                 if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::TEXTURE_ATLAS, t.second.get()->tag);
            }
        }
        if (ImGui::CollapsingHeader("Shaders")) {
            for (const auto& t : ResourceManager::Get().uShaders) {
                if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::SHADER, t.second.get()->tag);
            }
        }
        if(ImGui::CollapsingHeader("Engine Textures")) {
            for (const auto& t : ResourceManager::Get().uEngineTextures) {
                if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::ENGINE_TEXTURE, t.second.get()->tag);
            }
        }
        if (ImGui::CollapsingHeader("Engine TextureAtlases")) {
            for (const auto& t : ResourceManager::Get().uEngineTextureAtlases) {
                 if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::ENGINE_TEXTURE_ATLAS, t.second.get()->tag);
            }
        }
        if (ImGui::CollapsingHeader("Engine Shaders")) {
            for (const auto& t : ResourceManager::Get().uEngineShaders) {
                if (ImGui::Selectable(t.second.get()->tag.c_str()))
                    EngineData::SetSelected(SelectionType::ENGINE_SHADER, t.second.get()->tag);
            }
        }
        ImGui::End();
    }
};
struct ImGuiDebugPanel {
    void Draw() {
        ImGui::Begin("Debug Information");
        if (ImGui::TreeNode("Viewport Data")) {
            ImGui::Text("Mouse Position {%0.4f %0.4f}", Input.mouse.x, Input.mouse.y);
            ImGui::Text("Viewport Size {%d %d}", EngineData::CurrentScene().frameBuffer.GetWidth(), EngineData::CurrentScene().frameBuffer.GetHeight());
            ImGui::Text("ImGui Scale {%0.4f %0.4f}", WinData.xScale, WinData.yScale);
            ImGui::TreePop();
        }
        ImGui::Dummy({0, 20});
        if (ImGui::TreeNode("File Structure Information")) {
            ImGui::Text("Current Directory {%s}", EngineData::Get().state.currentDir.c_str());
            ImGui::Text("Project Root {%s}", EngineData::Get().state.openProjectRoot.c_str());           
            ImGui::TreePop();
        }
        ImGui::Dummy({0, 20});
        if (ImGui::TreeNode("Preferences")) {
            ImGui::Text("ResourcePanel: ");
            ImGui::TreePop();
        }
        ImGui::End();
    }
};
struct ImGuiPropertiesPanel {
    const float DRAW_SIZE = 256;
    struct CallbackData {
        std::string* registryId;
        std::string* displayName;
    };
    struct PropertiesCallbacks {
        static int DisplayNameChanged(ImGuiInputTextCallbackData* data) {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
                CallbackData* callbackdata = (CallbackData*)data->UserData;
            }
            return 0;
        }
    };
    void Draw() {
        ImGui::Begin("Properties");
        if (EngineData::Get().selectionType == SelectionType::NONE) {
            ImGui::End();
            return;
        }
        if (EngineData::Get().selectionType == SelectionType::ENTITY) {
            Entity* e = EngineData::CurrentScene().FindEntity(EngineData::Get().selectionId);
            DisplayComponents(e);
            AddComponentWigdet(e);
        }
        else if (EngineData::Get().selectionType == SelectionType::SIGNAL) {
            ImGui::Text("Signal");
        }
        else if (EngineData::Get().selectionType == SelectionType::TEXTURE) {
            ImGui::Text("Texture");
            Texture* t = ResourceManager::GetProjectResource<Texture>(EngineData::Get().selectionId);
            if (t != nullptr) {
                ImGui::Image((void*)(intptr_t) t->textureHandle, ImVec2{DRAW_SIZE, DRAW_SIZE}, ImVec2{0, 1}, ImVec2{1, 0});
            }
        }
        else if (EngineData::Get().selectionType == SelectionType::ENGINE_TEXTURE) {
            ImGui::Text("Texture");
            Texture* t = ResourceManager::GetEngineResource<Texture>(EngineData::Get().selectionId);
            if (t != nullptr) {
                ImGui::Image((void*)(intptr_t) t->textureHandle, ImVec2{DRAW_SIZE, DRAW_SIZE}, ImVec2{0, 1}, ImVec2{1, 0});
            }
        }
        else if (EngineData::Get().selectionType == SelectionType::TEXTURE_ATLAS) {
            ImGui::Text("Texture Atlas");
            TextureAtlas* a = ResourceManager::GetProjectResource<TextureAtlas>(EngineData::Get().selectionId);
            if (a != nullptr) {
                ImGui::Image((void*)(intptr_t) a->textureHandle, ImVec2{DRAW_SIZE, DRAW_SIZE}, ImVec2{0, 1}, ImVec2{1, 0});
            }
        }
        else if (EngineData::Get().selectionType == SelectionType::ENGINE_TEXTURE_ATLAS) {
            ImGui::Text("Texture Atlas");
            TextureAtlas* a = ResourceManager::GetEngineResource<TextureAtlas>(EngineData::Get().selectionId);
            if (a != nullptr) {
                ImGui::Image((void*)(intptr_t) a->textureHandle, ImVec2{DRAW_SIZE, DRAW_SIZE}, ImVec2{0, 1}, ImVec2{1, 0});
            }
        }
        else if (EngineData::Get().selectionType == SelectionType::SHADER) {
            ImGui::Text("Shader");
            Shader* s = ResourceManager::GetProjectResource<Shader>(EngineData::Get().selectionId);
            if (s != nullptr) {
                ImGui::Text("%s", s->tag.c_str());
            }
        }
        else if (EngineData::Get().selectionType == SelectionType::ENGINE_SHADER) {
            ImGui::Text("Shader");
            Shader* s = ResourceManager::GetEngineResource<Shader>(EngineData::Get().selectionId);
            if (s != nullptr) {
                ImGui::Text("%s", s->tag.c_str());
            }
        }
        ImGui::End();
    }
    
    void DisplayComponents(Entity* entity) {
        if (entity->HasComponent<Identifier>()) {
            if (ImGui::TreeNode("Identifier")) {
                CallbackData data;
                data.registryId = &entity->GetComponent<Identifier>().id;
                data.displayName = &entity->GetComponent<Identifier>().displayName;

                ImGui::Text("ID: %s", data.registryId->c_str());
                ImGui::InputText("Display Name: ", &*data.displayName, ImGuiInputTextFlags_CallbackEdit, PropertiesCallbacks::DisplayNameChanged, (void*)&data);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Relationship>()) {
            if (ImGui::TreeNode("Relationship")) {
                Relationship& r = entity->GetComponent<Relationship>();
                ImGui::Text("Parent : %s", r.parent.c_str());
                ImGui::Text("Level : %d", r.level);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Transform>()) {
            if (ImGui::TreeNode("Transform")) {
                Transform& t = entity->GetComponent<Transform>();
                ImGui::DragFloat2("Position", &t.position.x);
                ImGui::DragFloat2("Scale", &t.scale.x);
                ImGui::DragFloat("Rotation", &t.rotation);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Renderable>()) {
            if (ImGui::TreeNode("Renderable")) {
                CallbackData data;
                Renderable& r = entity->GetComponent<Renderable>();
                TextureAtlas* atlas = ResourceManager::GetProjectResource<TextureAtlas>(r.resourceId);
                ImGui::Image((void*)(intptr_t) atlas->textureHandle, ImVec2{64, 64}, ImVec2{0, 1}, ImVec2{1, 0});
                if (ImGui::BeginListBox("Subregions")) {
                    int id = 0;
                    for (auto& element : atlas->map) {
                        const bool is_selected = (r.atlasSubRegionName == element.first);
                        if (ImGui::Selectable(element.first.c_str(), is_selected)) {
                            LOG_DEBUG("Selected {}", element.first.c_str());
                            r.atlasSubRegionName = element.first;
                            r.region = Renderer2D::Get().textureAtlas->GetRegion(element.first);
                        }

                        if (is_selected)
                            ImGui::SetItemDefaultFocus();

                        id++;
                    }
                    ImGui::EndListBox();
                }
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<AnimatedRenderable>()) {
            if (ImGui::TreeNode("Animated Renderable")) {

                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Script>()) {
            if (ImGui::TreeNode("Script")) {
                Script& s = entity->GetComponent<Script>();
                ImGui::Text("%s", s.luaScriptPath.c_str());
            }
        }
        if (entity->HasComponent<SpriteRenderer>()) {
            if (ImGui::TreeNode("SpriteRenderer")) {
                SpriteRenderer& r = entity->GetComponent<SpriteRenderer>();
                ImGui::Text("Source Resource ID %s", r.resourceId.c_str());
                ImGui::Text("AtlasSubRegionName %s", r.atlasSubRegionName.c_str());
                ImGui::TreePop();    
            }
        }
    }

    void AddComponentWigdet(Entity* entity) {
        if (ImGui::Button("Add Component")) {
            ImGui::OpenPopup("add_component_popup");
        }
        if (ImGui::BeginPopup("add_component_popup")) {
            if (!entity->HasComponent<Identifier>() && ImGui::Button("Identifier")) {
                entity->AddComponent<Identifier>("");
            }
            if (!entity->HasComponent<Transform>() && ImGui::Button("Transform")) {
                entity->AddComponent<Transform>(0, 0, 32, 32, 0);
            }
            if (!entity->HasComponent<Renderable>() && ImGui::Button("Renderable")) {
                
            }
            if (!entity->HasComponent<AnimatedRenderable>() && ImGui::Button("AnimatedRenderable")) {
                entity->AddComponent<AnimatedRenderable>();
            }
            if (!entity->HasComponent<Script>() && ImGui::Button("Script")) {
                entity->AddComponent<Script>();
            }
            ImGui::EndPopup();
        }
    }
};
struct ImGuiViewportPanel {
    ImVec2 lastViewportSize;
    void Draw() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0, 0});
        ImGui::Begin("Viewport");
        //LOG_DEBUG("{} {}", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();
        ImVec2 vOffset = ImGui::GetWindowPos();
        vMin.x += vOffset.x;    //topleft
        vMin.y += vOffset.y;    //
        vMax.x += vOffset.x;    //bottomright
        vMax.y += vOffset.y;    //
       
        ImVec2 mousePos = ImGui::GetMousePos(); //mousePos;
        Input.mouse.x = mousePos.x - vMin.x;    //subtract left edge from xCoord
        Input.mouse.y = mousePos.y - vMin.y;

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        ImGuiIO& io = ImGui::GetIO();

        //LOG_DEBUG("Drawing framebuffer");
        GLuint texId = EngineData::CurrentScene().frameBuffer.GetColorAttachment();
        ImGui::Image((void*)(intptr_t) texId, viewportSize);

        Scene* scene = &EngineData::Get().CurrentScene();
        Entity* e = scene->FindEntity(EngineData::Get().SelectedEntity());
        if (e) {
            ImGuizmo::SetOrthographic(true);
            ImGuizmo::SetDrawlist();

            float winWidth = (float) ImGui::GetWindowWidth();
            float winHeight = (float) ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, winWidth, winHeight);
            
            const auto& proj = scene->cam.GetProj();
            const auto view = scene->cam.GetView();
            Transform& t = e->GetComponent<Transform>();
             
            switch (EngineData::Get().currentOperation) {
                case ImGuizmo::OPERATION::TRANSLATE:
                    //show and manipulate translation gizmo
                    break;
                case ImGuizmo::OPERATION::ROTATE:
                    //show and manipulate rotation gizmo
                    break;
                case ImGuizmo::OPERATION::SCALE:
                    //show and manipulate scale gizmo
                    break;
                case -1:
                    //do nothing
                    break;
                default:
                    LOG_CRITICAL("Unhandled ImGuimo State");
            }
            ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(proj), 
                    ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, glm::value_ptr(t.transform));
        }
        EngineData::CurrentScene().focused = ImGui::IsWindowFocused();

        if (lastViewportSize.x != viewportSize.x || lastViewportSize.y != viewportSize.y) {
            EngineData::CurrentScene().OnResize(viewportSize.x, viewportSize.y);
            lastViewportSize = { viewportSize.x, viewportSize.y };
        }
        
        ImGui::End();
        ImGui::PopStyleVar();
    }
};
struct ImGuiScriptEditorPanel {
    void Draw() {
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
        ImGui::Begin("ScriptEditor");
        if (ImGui::IsWindowFocused()) {
            
        }
        if (ImGui::Button("Save")) LOG_DEBUG("Saving file");
        ImGui::InputTextMultiline("Source code", 
                EngineData().Get().scriptText, 
                IM_ARRAYSIZE(EngineData::Get().scriptText),
                ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16),
                flags);
        ImGui::End();
    }
};
struct ImGuiFileManagerPanel {
    ImGuiFileManagerPanel()
    {
    }
    void Draw() {
        ImGui::Begin("File Manager");
      
        if (EngineData::Get().state.openProjectRoot.empty()) {
            float w = ImGui::GetWindowWidth();
            float h = ImGui::GetWindowHeight();
            ImGui::SetCursorPos({w/2 - 20, h/2});
            ImGui::Text("No project directory selected");
            ImGui::End();
            return;
        }

        if (EngineData::Get().state.currentDir != EngineData::Get().state.openProjectRoot) {
            if (ImGui::Button("<-")) {
                EngineData::Get().state.currentDir = EngineData::Get().state.currentDir.parent_path();
            }
        }

        const int itemSpacing = 16;
        const int columnsWide = ImGui::GetWindowContentRegionWidth() / 128;
        ImGui::BeginTable("File Manager", columnsWide);
        
        ImGui::TableNextColumn();
        int id = 0;
        for (auto& p : std::filesystem::directory_iterator(EngineData::Get().state.currentDir)) {
            const auto& path = p.path();
            auto relPath = std::filesystem::relative(path, EngineData::Get().state.openProjectRoot);
            std::string filenameStr = relPath.filename().string();
           
            if (filenameStr != ".DS_Store") {
                Texture* folderTex = ResourceManager::GetEngineResource<Texture>("folder_icon");
                Texture* fileTex = ResourceManager::GetEngineResource<Texture>("file_icon");
                ImGui::PushID(id);           
            
                if (p.is_directory()) {
                    if (ImGui::ImageButton((void*)(intptr_t) folderTex->textureHandle, ImVec2{128, 128}, ImVec2{0, 1}, ImVec2{1, 0})) {
                        LOG_DEBUG("Move directories");
                        EngineData::Get().state.currentDir /= path.filename();
                    }
                    ImGui::Text("%s", filenameStr.c_str());
                }
                else {
                    if (ImGui::ImageButton((void*)(intptr_t) fileTex->textureHandle, ImVec2{128, 128}, ImVec2{0, 1}, ImVec2{1, 0})) {
                        LOG_DEBUG("Open file");
                    }
                    ImGui::Text("%s", filenameStr.c_str());
                }

                ImGui::PopID();
                id++;

                ImGui::TableNextColumn();
            }
        }
        ImGui::EndTable();

        ImGui::End();
    }  
};
struct ImGuiSceneHeirarchy {
    void Draw() {
        ImGui::Begin("Scene Heirarchy");
        Scene* scene = &EngineData::CurrentScene();
        if (ImGui::CollapsingHeader("Entities")) {
            DrawHeirarchy(scene->root.get());
        }
        ImGui::End();
    }

    void DrawHeirarchy(Entity* entity) {
        Scene* scene = &EngineData::CurrentScene();
        ImGuiTreeNodeFlags flags = (EngineData::Get().selectionId == entity->GetComponent<Identifier>().id ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        auto& id = entity->GetComponent<Identifier>().id;
        
        if (DrawNode(entity, id)) {
            for (auto& id : entity->GetChildren()) {
                Entity* e = scene->FindEntity(id);
                if (e->GetParent() == entity->GetComponent<Identifier>().id) {
                    DrawHeirarchy(e);
                }
            }
            ImGui::TreePop();
        }
    }

    bool DrawNode(Entity* entity, const std::string& id) {
        ImGuiTreeNodeFlags flags = (EngineData::Get().selectionId == id ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx(id.c_str(), flags);
        if (ImGui::IsItemClicked()) {
            LOG_DEBUG("Clicked {}", id.c_str());
            if (id != "root") {
                EngineData::Get().selectionId = id;
                EngineData::Get().selectionType = SelectionType::ENTITY;
            }
        }
        return opened;
    }
};
struct ImGuiPreferencesPanel {
    void Draw() {
        ImGui::Begin("Preferences");
        ImGui::End();
    }
};
struct ImGuiControlsBarPanel {
    void Draw() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 2});
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, {0, 0});
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0, 0});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.3f, 0.305f, 0.31f, 0.5f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.305f, 0.31f, 0.5f});

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= ImGuiWindowFlags_NoScrollbar;
        flags |= ImGuiWindowFlags_NoScrollWithMouse;
        flags |= ImGuiWindowFlags_NoResize;

        ImGui::Begin("Controls", nullptr, flags);
        Scene* scene = &EngineData::CurrentScene();
        Texture* icon = scene->State() == SceneState::STOPPED ? 
            ResourceManager::GetEngineResource<Texture>("play_icon"):
            ResourceManager::GetEngineResource<Texture>("stop_icon");

        float size = ImGui::GetWindowHeight() - 4.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        if (ImGui::ImageButton((void*)(intptr_t) icon->textureHandle, ImVec2 {20, 20})) {
            if (scene->State() == SceneState::STOPPED) {
                scene->Start();
            }
            else if (scene->State() == SceneState::PLAYING) {
                scene->Stop();
            }
        }
        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);
        ImGui::End();
    }
};

class ImGuiLayer {
public:
    static ImGuiLayer Get() {
        static ImGuiLayer imguilayer;
        return imguilayer;
    }
    static void Init() {

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGuiIO& io = ImGui::GetIO();
        
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.WantSaveIniSettings = true;
        //ImGuiLayer::Get().font = io.Fonts->AddFontFromFileTTF("res/engine_files/fonts/Montserrat-Light.tff", 16.0f);
        //io.ConfigDockingWithShift = true;
       
        LOG_DEBUG("Initialized ImGuiLayer");
    }
    static void Draw() {
        ShowDockspace();
    }

private:
    static void ShowDockspace() {
        static bool dockspace_open = true;
        static bool opt_fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        //setup styles
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1);
        ImGui::Begin("DockSpace Demo", &dockspace_open, window_flags);

        ImGui::GetIO().DisplayFramebufferScale.x = WinData.xScale;
        ImGui::GetIO().DisplayFramebufferScale.y = WinData.yScale;

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)  {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMenuButtonPosition = 2;

        DrawUI();

        ImGui::End();
        ImGui::PopStyleVar();
    }
    
    static void DrawUI() {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::PushFont(Get().font);
        Get().menuPanel.Draw();
        
        if (EngineData::Preferences().isSignalPanelEnabled)
            Get().signalsPanel.Draw();
        
        if (EngineData::Preferences().isViewportPanelEnabled)
            Get().viewportPanel.Draw();
        
        if (EngineData::Preferences().isResourcePanelEnabled)
            Get().resourcesPanel.Draw();
        
        if (EngineData::Preferences().isDebugPanelEnabled)
            Get().debugPanel.Draw();
        
        if (EngineData::Preferences().isPropertiesPanelEnabled)
            Get().propertiesPanel.Draw();
       
        if (EngineData::Preferences().isScriptEditorPanelEnabled)
            Get().scriptEditor.Draw();
        
        if (EngineData::Preferences().isFileManagerPanelEnabled)
            Get().fileManager.Draw();

        if (EngineData::Preferences().isSceneHeirarchyPanelEnabled)
            Get().sceneHeirarchyPanel.Draw();

        if (EngineData::Preferences().isPreferencesWindowEnabled)
            Get().preferencesPanel.Draw();
       
        if (EngineData::Preferences().isControlsBarPanelEnabled)
            Get().controlsPanel.Draw();

        if (EngineData::Preferences().isDemoWindowEnabled)
            ImGui::ShowDemoWindow();

        ImGui::PopFont();
    }

private:
    //https://pastebin.com/kNEH7KjK
    void InitColorTheme(ImGuiStyle* dst) {
        ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
        ImVec4* colors = style->Colors;
    }
private:
    ImGuiMenuPanel menuPanel;
    ImGuiViewportPanel viewportPanel;
    ImGuiDebugPanel debugPanel;
    ImGuiPropertiesPanel propertiesPanel;
    ImGuiSignalsPanel signalsPanel;
    ImGuiResourcesPanel resourcesPanel;
    ImGuiScriptEditorPanel scriptEditor;
    ImGuiFileManagerPanel fileManager;
    ImGuiSceneHeirarchy sceneHeirarchyPanel;
    ImGuiPreferencesPanel preferencesPanel;
    ImGuiControlsBarPanel controlsPanel;

public:
    ImFont* font;

public:
    friend class Window;
};
}
