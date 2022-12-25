#ifndef CECS_REGISTRY_HPP_0660
#define CECS_REGISTRY_HPP_0660

#include "Entity.hpp"

#include <vector>
#include <random>

namespace CECS {
    class Registry {
    private:
        std::vector<Entity*> entities;
    public:
        template<typename T>
        Entity& Create() {
            UUID uuid;
            Entity* entity = new Entity(uuid);
            entity->AddComponent<T>();
            entities.push_back(entity);
            return *entity;
        }
        void Destroy(Entity& entity) {
            auto it = std::find_if(entities.begin(), entities.end(), [&](Entity* ptr) {
                    return std::equal_to<Entity*>()(ptr, &entity);
                });
            if (it != entities.end()) {
                delete* it;
                entities.erase(it);
            }
        }
        template<typename Func>
        void Each(Func&& func) {
            for (auto& entity : entities) {
                func(*entity);
            }
        }
    };
}

#endif // CECS_REGISTRY_HPP_0660
