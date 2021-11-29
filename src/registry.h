#pragma once

#include "corepch.h"
#include "entt/signal/dispatcher.hpp"
#include <entt/entt.hpp>
#include <memory>
#include <unordered_map>
#include <type_traits>
#include "components/components.h"
#include "imgui.h"

class GameObject {
public:
    GameObject(entt::registry &reg) {
        entityHandle = reg.create();
    }

    entt::entity entityHandle;
};

class Registry {
public:
    static Registry& Get() {
        static Registry registry;
        return registry;
    }

    //
    //Registration
    //
    static GameObject& RegisterGameObject(const std::string& name) {
        if (Get().entities.find(name) != Get().entities.end()) {
            LOG_WARN("Object already exists, returning existing object.");
        } else {
            Get().entities.emplace(name, std::make_unique<GameObject>(Get().reg));
            LOG_DEBUG("Registerd GameObject - {}", name);
        }
        return GetRegisteredGameObject(name);
    }

    static bool DeleteGameObject(const std::string& name) {
        if (Get().entities.find(name) != Get().entities.end()) {
            Get().reg.destroy(GetRegisteredGameObject(name).entityHandle);
            Get().entities.erase(Get().entities.find(name));
            return true;
        }
        return false;
    }
    
    static bool DeleteGameObject(const GameObject& object) {
        LOG_WARN("Deleting gameobject by reference is not implemented");
        return false;
    }

    static GameObject& GetRegisteredGameObject(const std::string& name) {
        return *Get().entities.at(name).get();
    }
    
    //
    //AddComponent
    //
    template <typename T, typename ...Args>
    static void AddComponent(const GameObject& object, Args&&... args) {
        Get().reg.emplace<T>(object.entityHandle, std::forward<Args>(args)...);
        LOG_DEBUG("Added Component");
    }

    template <typename T, typename ...Args>
    static void AddComponent(const std::string& name, Args&&... args) {
        Get().reg.emplace<T>(Get().entities.at(name)->entityHandle, std::forward<Args>(args)...);
        LOG_DEBUG("Added Component");
    }

    //
    //GetComponent
    //
    template <typename T>
    static T& GetComponent(const GameObject& object) {
        return Get().reg.get<T>(object.entityHandle);
    }

    template <typename T>
    static T& GetComponent(const std::string& name) {
        return Get().reg.get<T>(Get().entities.at(name)->entityHandle);
    }

    //
    //HasComponent
    //
    template <typename T>
    static bool HasComponent(const GameObject& object) {
        return Get().reg.try_get<T>(object.entityHandle);
    }

    template <typename T>
    static bool HasComponent(const std::string& name) {
        return Get().reg.try_get<T>(Get().entities.at(name)->entityHandle);
    }

    //
    //BehaviorComponent
    //T must be inherited from Behavior
    //
    template <typename T>
    static void AddBehavior(const GameObject& object) {
        static_assert(std::is_base_of<Behavior, T>::value, "Not derived from Behavior");
        AddComponent<T>(object, GetComponent<Identifier>(object).id);
    }

    template <typename T>
    static void AddBehavior(const std::string& name) {
        static_assert(std::is_base_of<Behavior, T>::value, "Not derived from Behavior");
        AddComponent<T>(name, GetComponent<Identifier>(name).id);
    }

    //
    //GameObject Initialization
    //
    static void InitializeGO(GameObject& object) {
    
    }

    static void SortByTexture() {
        LOG_DEBUG("Texture sorting not implemented... WIP");
    }

    //
    //Signal Handling (WIP)
    //
    template <typename T>
    static void RegisterSignal(void* function) {
        LOG_WARN("Signals not implemented yet");
        //Get().dispatcher.sink<T>().connect<&function>()
    }

    template <typename T, typename ...Args>
    static void EmitSignal(Args&&... args) {
        Get().dispatcher.trigger<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename ...Args>
    static void QueueSignal(Args&&... args) {
        Get().dispatcher.enqueue<T>(std::forward<Args>(args)...);
    }

    static void EmitQueue() {
        Get().dispatcher.update();
    }

    template <typename T>
    static void EmitQueue() {
    }

private:
    entt::registry reg = {};
    entt::dispatcher dispatcher;

    //TODO: Fundamentally this makes little sense as it should be sortable
    //          in order to allow for more efficient rendering
    std::map<std::string, std::unique_ptr<GameObject>> entities;

    friend class Renderer2D;
    friend class ImGuiLayer;
};

