#include "../registry.h"
#include "../renderer/renderer2D.h"
#include "../util/resourceManager.h"
#include "../window/inputData.h"
#include "imgui/imgui.h"

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
        //io.ConfigDockingWithShift = true;
        //
        LOG_DEBUG("Initialized ImGuiLayer");
    }

    static void Draw() {
        ShowDockspace();
    }

private:
    static void ShowDockspace() {
        static bool dockspace_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
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

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        ImGui::Begin("DockSpace Demo", &dockspace_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);

                if (ImGui::MenuItem("Quit")) dockspace_open = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        
        DrawUI();

        ImGui::End();
    }
    
    static void DrawUI() {
        DrawRegistry();
        DrawSignals();
        DrawViewport();
        DrawResources();
        DrawStatistics();
    }

    static void DrawRegistry() {
        ImGui::Begin("Registry");
        if (ImGui::CollapsingHeader("GameObjects")) {
            ImGuiIO& io = ImGui::GetIO();
            for (const auto &entry : Registry::Get().entities) {
                std::string objectId = Registry::GetComponent<Identifier>(entry.first).id;
                if (ImGui::TreeNode(objectId.c_str())) {
                    ImGui::Text("Display GameObject's components here");
                    if (ImGui::Button("AddComponent")) {
                        LOG_DEBUG("Adding components via gui work in progress");
                    }
                    ImGui::TreePop();
                }
            }
        }
        ImGui::End();
    }

    static void DrawSignals() {
        ImGui::Begin("Signals");
        if (ImGui::CollapsingHeader("Signals")) {
            ImGui::Text("Signals WIP");
        }
        ImGui::End();
    }

    static void DrawViewport() {
        ImGui::Begin("Viewport");
        /*
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (Get().viewportSize != *((glm::vec2*)&viewportPanelSize)) {
            LOG_INFO("Resize window");
            Renderer2D::Get().frameBuffer.Resize((uint32_t) viewportPanelSize.x, (uint32_t) viewportPanelSize.y);
            Get().viewportSize = {viewportPanelSize.x, viewportPanelSize.y};
        }
        */
        GLuint texId = Renderer2D::Get().frameBuffer.GetColorAttachment();
        ImGui::Image((void*)(intptr_t) texId, ImVec2{ 1280, 720 });
        ImGui::End();
    }

    static void DrawResources() {
        ImGui::Begin("Resources");
        if(ImGui::CollapsingHeader("Textures")) {
            for (const auto& t : ResourceManager::Get().uTextures) {
                ImGui::Text("%s", t.second.get()->tag.c_str());
            }
        }
        if (ImGui::CollapsingHeader("TextureAtlases")) {
            for (const auto& t : ResourceManager::Get().uTextureAtlases) {
                ImGui::Text("%s", t.second.get()->tag.c_str());
            }
        }
        if (ImGui::CollapsingHeader("Shaders")) {
            for (const auto& t : ResourceManager::Get().uShaders) {
                ImGui::Text("%s", t.second.get()->tag.c_str());
            }
        }
        ImGui::End();
    }

    static void DrawStatistics() {
        ImGui::Begin("Statistics");
        ImGui::Text("Mouse Position {%0.4f %0.4f}", Input.mouse.x, Input.mouse.y);
        ImGui::Text("Viewport Size {%0.4f %0.4f}", Get().viewportSize.x, Get().viewportSize.y);
    }
public:
    glm::vec2 viewportSize = {10, 10};

    friend class Window;
};
