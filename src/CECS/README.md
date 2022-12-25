## CECS (Clegine Entity Component System) Framework C++
Simple header-only ECS (Entity Component System) framework that only for Clegine Core. 
This ECS (Entity Component System) is part of Clegine Core Component.
ECS will be placed inside Clegine Core cause the developer is dumb for making it into a dynamic library. Thank you!

### Example
```cpp
#include <CECS.hpp>
#include <glm.hpp>

struct TransformComponent : public CECS::IComponent {
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
}

struct Camera : public CECS::IComponent {

}

int main() {
	// Create main Registry from CECS namespace
	CECS::Registry registry;
	// Entity is default class from CECS.
	// You can use your own custom Entity class in the future!
	CECS::Entity object = registry.Create<TransformComponent>();
	CECS::Entity camera = registry.create<TransformComponent>();
	camera.AddComponent<CameraComponent>(camera);

	// Get TransformComponent Position value
	auto& objectPos = registry.GetComponent<TransformComponent>()->Position;

	// Now, 'objectPos' has value 'glm::vec3'. Lets manipulate the variable
	objectPos.x = 2.5f;
	objectPos.y = 5.0f;
	objectPos.z = 0.0f;

	// This will iterate all created entity from registry
	registry.Each([](auto& entity) {
		
	});
	return 0;
}
```

### Available Function

CECS Registry
- Create
- Destroy
- Each

CECS Entity
- AddComponent
- RemoveComponent
- GetComponent
- CopyComponent
- GetComponentSize
- IsComponentEqual / IsComponentSame (CECS 1.1)

### Documentation
Soontm