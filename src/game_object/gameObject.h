#pragma once
#include <entt/entt.hpp>

class GameObject {
public:
    GameObject(entt::registry& reg);
    ~GameObject();

    template <typename T, class ...Args>
    void AddComponent(Args&&... args) {
        reg.emplace<T>(entity, std::forward<Args>(args)...);
    }
     
    template <typename T>
    T& GetComponent() {
        if (!HasComponent<T>()) {
            //AddComponent<T>();
        }
        return reg.get<T>(entity);
    }

    template <typename T>
    bool HasComponent() {
        return reg.try_get<T>(entity);
    }

private:
    entt::entity entity;
    entt::registry& reg;
};
