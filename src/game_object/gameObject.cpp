#include "gameObject.h"

GameObject::GameObject(entt::registry& reg)
:reg(reg) {
    entity = reg.create();
}

GameObject::~GameObject() {

}

//AddComponent declared / defined in header
//GetComponent declared / defined in header
