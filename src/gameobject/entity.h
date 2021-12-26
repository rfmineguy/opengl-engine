#pragma once
#include <entt/entt.hpp>
#include "../corepch.h"
#include "../engine/scene.h"
#include "../components/components.h"

namespace Firefly {
class Entity {
public:
    Entity(Scene* scene, const std::string& id)
    :mScene(scene), id(id) {
        handle = scene->reg.create();
    }

    template <typename T>
    T& GetComponent() {
        if (!HasComponent<T>()) {
            LOG_CRITICAL("Component not found {}", typeid(T).name());
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

    void AddChild(const std::string& _id) {
        int parentLevel = this->GetComponent<Relationship>().level;
        this->GetComponent<Relationship>().isParent = true;
        this->GetComponent<Relationship>().children.push_back(_id);
        mScene->FindEntity(_id)->GetComponent<Relationship>().level = parentLevel + 1;
        mScene->FindEntity(_id)->GetComponent<Relationship>().isChild = true;
        mScene->FindEntity(_id)->GetComponent<Relationship>().parent = this->id;
    }

    void AddChild(Entity* entity) {
        AddChild(entity->id);
    }

    std::vector<std::string> GetChildren() {
        if (this->GetComponent<Relationship>().isParent) {
            return this->GetComponent<Relationship>().children;
        }
        return {};
    }

    bool HasChildren() {
        return GetChildren().size() > 0;
    }

    std::string& GetParent() {
        return this->GetComponent<Relationship>().parent;
    }

    void SetDirty() { isDirty = true; }

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
    bool isDirty = false;
    std::string id;
    entt::entity handle {entt::null};
    Scene* mScene = nullptr;
};
}
