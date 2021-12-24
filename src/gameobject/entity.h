#pragma once
#include <entt/entt.hpp>
#include "../corepch.h"
#include "../engine/scene.h"

namespace Firefly {
class Entity {
public:
    Entity(Scene* scene)
    :mScene(scene) {
        handle = scene->reg.create();
    }

    template <typename T>
    T& GetComponent() {
        if (!HasComponent<T>()) {
            LOG_CRITICAL("Component not found");
        }
        return mScene->reg.get<T>(handle);
    }

    template <typename T>
    bool HasComponent() {
        return mScene->reg.try_get<T>(handle);
    }

    template <typename T, typename ...Args>
    void AddComponent(Args&&... args) {
        mScene->reg.emplace<T>(handle, std::forward<Args>(args)...);
    }

    template <typename T>
    void RemoveComponent() {
        mScene->reg.remove<T>(handle);
    }

	operator bool() const { return handle != entt::null; }
	operator entt::entity() const { return handle; }
	operator uint32_t() const { return (uint32_t)handle; }

	bool operator==(const Entity& other) const
	{
		return handle == other.handle && mScene == other.mScene;
	}

	bool operator!=(const Entity& other) const
	{
		return !(*this == other);
	}
private:
    entt::entity handle {entt::null};
    Scene* mScene = nullptr;
};
}
