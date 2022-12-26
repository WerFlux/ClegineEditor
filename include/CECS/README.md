## CECS (Clegine Entity Component System) Framework C++
Is a simple header-only ECS (Entity Component System) framework that only for Clegine Core. 

### Example
```cpp
#include <CECS.hpp>
#include <glm.hpp>
#include <iostream>

struct TransformComponent : public CECS::IComponent {
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
}

struct CameraComponent : public CECS::IComponent {
	// Camera Code
}

int main() {
	// Create main Registry instances from CECS namespace
	CECS::Registry registry;
	// Create Entity using Registry Create (you can use "using namespace CECS" if you want to)
	CECS::Entity object = registry.Create<TransformComponent>();
	CECS::Entity camera = registry.create<TransformComponent>();
	// Add CameraComponent to camera Entity
	camera.AddComponent<CameraComponent>();

	// Expected to output: Camera has 2 components!
	std::cout << "Camera has " << camera.GetComponentSize() << " components!\n";

	// Get TransformComponent Position value
	auto& objectPos = object.GetComponent<TransformComponent>()->Position;

	// Now, 'objectPos' has value 'glm::vec3'. Lets manipulate the variable
	objectPos.x = 2.5f;
	objectPos.y = 5.0f;
	objectPos.z = 0.0f;

	// This will iterate all created entity from registry
	registry.Each([](auto& entity) {
		
	});

	// Meh, this Camera is useless
	registry.Destroy(camera);
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
- GetUUID

### Documentation
Coming Soon!