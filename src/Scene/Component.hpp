#ifndef CLEGINE_SCENE_COMPONENT_HPP
#define CLEGINE_SCENE_COMPONENT_HPP

#include <EntryPoint.hpp>

namespace Clegine {
	struct TransformComponent : public CECS::IComponent {
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		glm::mat4 GetRealTransform() const {
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct CameraComponent : public CECS::IComponent {

	};
}

#endif // CLEGINE_SCENE_COMPONENT_HPP
