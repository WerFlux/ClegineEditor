#ifndef CLEGINE_RENDERER_ORTHO_CAMERA_HPP
#define CLEGINE_RENDERER_ORTHO_CAMERA_HPP

#include <Core/Singleton.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Clegine {
	class OrthoCamera : public Singleton<OrthoCamera> {
	public:
		OrthoCamera() = default;

		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::mat4& GetProjection() const { return projection; }
	private:
		glm::mat4 projection;
	};
}

#endif // CLEGINE_RENDERER_ORTHO_CAMERA_HPP