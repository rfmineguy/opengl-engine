#include "gameObject.h"

GameObject::GameObject(entt::registry& reg)
:reg(reg) {
    entity = reg.create();
}

GameObject::~GameObject() {
    reg.destroy(entity);
    LOG_WARN("Deleting gameobject");
}

GameObject::GameObject(GameObject&& other)
:reg(other.reg) {
    entity = other.entity;
}

//AddComponent declared / defined in header
//GetComponent declared / defined in header
