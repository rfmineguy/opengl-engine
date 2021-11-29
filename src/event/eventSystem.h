#include "../corepch.h"
#include "entt/signal/dispatcher.hpp"
#include "events.h"

class EventSystem {
public:
    static EventSystem& Get() {
        static EventSystem eventSystem;
        return eventSystem;
    }
   
    template <typename T>
    static void registerEvent() {
        
    }

    template <typename T>
    static void connectListener(std::function<void()> func) {
        Get().dispatcher.sink<T>().connect(func);
    }

    template <typename T, class ...Args>
    static void emit(Args&&... args) {
        Get().dispatcher.trigger<T>(std::forward<Args>(args)...);
    }

    template <typename T, class ...Args>
    static void queue(Args&&... args) {
        Get().dispatcher.enqueue<T>(std::forward<Args>(args)...);
    }

    static void updateAll() {
        Get().dispatcher.update();
    }
    
    template <typename T>
    static void update() {
        Get().dispatcher.update<T>();
    }

private:
    entt::dispatcher dispatcher = {};
};
