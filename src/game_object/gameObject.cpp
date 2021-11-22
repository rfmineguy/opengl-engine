#include "gameObject.h"
#include "../components/components.h"
#include "entt/entity/entity.hpp"

GameObject::GameObject(entt::registry& reg)
:reg(reg){
    entity = reg.create();
}

GameObject::~GameObject() {
    LOG_WARN("Deleting gameobject {}", GetComponent<Identifier>().id);
    reg.destroy(entity);
}

GameObject::GameObject(GameObject&& other)
:reg(other.reg) {
    LOG_DEBUG("Moving GameObject {}", other.GetComponent<Identifier>().id);
    entity = other.entity;
    other.entity = entt::null;
}

//AddComponent declared / defined in header
//GetComponent declared / defined in header
