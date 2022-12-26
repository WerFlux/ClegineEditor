#include "CECS.hpp"

#include <iostream>

struct TransformComponent : public CECS::IComponent {
	float pos = 0.0f;
};

struct CameraComponent : public CECS::IComponent {

};

struct RenderComponent : public CECS::IComponent {

};

int main() {
	CECS::Registry registry;
	CECS::Entity entity1 = registry.Create<TransformComponent>();
	CECS::Entity entity2 = registry.Create<RenderComponent>();

	std::cout << entity1.GetComponentSize() << '\n';
	std::cout << entity2.GetComponentSize() << '\n';

	auto& manipulate1 = entity1.GetComponent<TransformComponent>()->pos;
	manipulate1 = 5.0f;
	std::cout << entity1.GetComponent<TransformComponent>()->pos << '\n';
	
	entity1.CopyComponent<TransformComponent>(entity2);
	std::cout << entity2.GetComponent<TransformComponent>()->pos << '\n';

	std::cout << entity1.GetComponentSize() << '\n';
	std::cout << entity2.GetComponentSize() << '\n';

	registry.Each([&](auto& entity) {
		std::cout << entity.GetUUID() << '\n';
	});
	return 0;
}