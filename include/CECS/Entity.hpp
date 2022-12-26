#ifndef CECS_ENTITY_HPP_0660
#define CECS_ENTITY_HPP_0660

#include "UUID.hpp"

#include <typeindex>
#include <unordered_map>

namespace CECS {
    struct IComponent { };
    class Entity {
    private:
        UUID uuid;
		std::unordered_map<std::type_index, IComponent> components;
	public:
        Entity() = default;
        Entity(const UUID& otherUuid) : uuid(otherUuid) { };
		template<typename T>
		bool AddComponent() noexcept {
			if (components.count(std::type_index(typeid(T))) == 0) {
				components[std::type_index(typeid(T))] = IComponent();
				return true;
			}
			return false;
		}
		template<typename T>
		T* GetComponent() noexcept {
			auto it = components.find(std::type_index(typeid(T)));
			if (it == components.end()) {
				return nullptr;
			}
			return static_cast<T*>(&it->second);
		}
        template<typename T>
        bool RemoveComponent() {
            auto it = components.find(std::type_index(typeid(T)));
            if (it == components.end()) {
                return false;
            }
            components.erase(it);
            return true;
        }
        template<typename T>
        bool CopyComponent(Entity& other) noexcept {
            if (components.count(std::type_index(typeid(T))) == 0) {
                return false;
            }
            if (other.components.count(std::type_index(typeid(T))) != 0) {
                return false;
            }
            T temp = *GetComponent<T>();
            RemoveComponent<T>();
            other.AddComponent<T>();
            *other.GetComponent<T>() = temp;
            return true;
        }
        std::size_t GetComponentSize() const noexcept {
            return components.size();
        }
        std::string GetUUID() noexcept {
            return uuid.Get();
        }
    };
}

#endif // CECS_ENTITY_HPP_0660
