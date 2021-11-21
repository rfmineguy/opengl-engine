#pragma once
#include <entt/entt.hpp>
#include "../util/log.h"

class GameObject {
public:
    GameObject(entt::registry& reg);
    ~GameObject();
    GameObject(const GameObject& other) = default;
    GameObject(GameObject&& GameObject);

    template <typename T, class ...Args>
    void AddComponent(Args&&... args) {
        //LOG_DEBUG("Adding component");
        reg.emplace<T>(entity, std::forward<Args>(args)...);
    }
    
    template <typename T>
    T& GetComponent() {
        //LOG_DEBUG("Getting component");
        return reg.get<T>(entity);
    }

    template <typename T>
    bool HasComponent() {
        //LOG_DEBUG("Looking for component");
        return reg.try_get<T>(entity);
    }

    void ListComponents() {
        
    }

private:
    entt::entity entity;
    entt::registry& reg;
};
